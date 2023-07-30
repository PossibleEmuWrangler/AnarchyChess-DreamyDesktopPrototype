/*  DreamChess
**
**  DreamChess is the legal property of its developers, whose names are too
**  numerous to list here. Please refer to the AUTHORS.txt file distributed
**  with this source distribution.
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <windows.h>

#include "debug.h"
#include "dreamchess.h"
#include "pipe_win32.h"

static int init_ok = 0;
static HANDLE hProcess;

int comm_init(char *engine) {
	HANDLE to_child_rd, to_child_wr, to_child_wr_dup, from_child_rd, from_child_wr, from_child_rd_dup, h_stdout;

	SECURITY_ATTRIBUTES sa_attr;

	PROCESS_INFORMATION proc_info;
	STARTUPINFO start_info;

	/* Make pipe handles inherited. */

	sa_attr.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa_attr.bInheritHandle = TRUE;
	sa_attr.lpSecurityDescriptor = NULL;

	/* Get the STDOUT handle. */

	h_stdout = GetStdHandle(STD_OUTPUT_HANDLE);

	/* Create a pipe for input from child. */

	if (!CreatePipe(&from_child_rd, &from_child_wr, &sa_attr, 0)) {
		DBG_ERROR("Failed to create stdout pipe");
		exit(1);
	}

	/* Make a non-inheritable copy of the read handle and close the original
	** one.
	*/

	if (!DuplicateHandle(GetCurrentProcess(), from_child_rd, GetCurrentProcess(), &from_child_rd_dup, 0, FALSE,
						 DUPLICATE_SAME_ACCESS)) {
		DBG_ERROR("Failed to duplicate read handle");
		exit(1);
	}
	CloseHandle(from_child_rd);

	/* Create a pipe for output to child. */

	if (!CreatePipe(&to_child_rd, &to_child_wr, &sa_attr, 0)) {
		DBG_ERROR("Failed to create stdin pipe");
		exit(1);
	}

	/* Make a non-inheritable copy of the write handle and close the original
	** one.
	*/

	if (!DuplicateHandle(GetCurrentProcess(), to_child_wr, GetCurrentProcess(), &to_child_wr_dup, 0, FALSE,
						 DUPLICATE_SAME_ACCESS)) {
		DBG_ERROR("Failed to duplicate write handle");
		exit(1);
	}
	CloseHandle(to_child_wr);

	/* Create child process. */

	ZeroMemory(&proc_info, sizeof(PROCESS_INFORMATION));

	ZeroMemory(&start_info, sizeof(STARTUPINFO));
	start_info.cb = sizeof(STARTUPINFO);
	start_info.hStdError = from_child_wr;
	start_info.hStdOutput = from_child_wr;
	start_info.hStdInput = to_child_rd;
	start_info.dwFlags |= STARTF_USESTDHANDLES;

	if (!CreateProcess(NULL, engine, NULL, NULL, TRUE, DETACHED_PROCESS, NULL, NULL, &start_info, &proc_info)) {
		DBG_ERROR("Failed to create child process");
		init_ok = 0;
		return 1;
	}

	hProcess = proc_info.hProcess;

	/* Close unneeded handle. */
	CloseHandle(proc_info.hThread);

	pipe_win32_init(from_child_rd_dup, to_child_wr_dup, 0);
	init_ok = 1;
	return 0;
}

void comm_exit(void) {
	if (init_ok) {
		DBG_LOG("Waiting for engine to exit");

		if (WaitForSingleObject(hProcess, INFINITE) != WAIT_FAILED) {
			DBG_LOG("Engine exitted succesfully");
			CloseHandle(hProcess);
		} else {
			DBG_ERROR("Error while waiting for engine to quit");
			exit(1);
		}

		pipe_win32_exit();
	}
}

void comm_send_str(char *str) {
	if (init_ok)
		pipe_win32_send(str);
}

char *comm_poll(void) {
	if (init_ok) {
		DWORD exit;
		int error;

		GetExitCodeProcess(hProcess, &exit);

		if (exit == STILL_ACTIVE) {
			char *retval = pipe_win32_poll(&error);
			if (!error)
				return retval;
		} else {
			DBG_ERROR("Engine process has terminated");
		}

		pipe_win32_exit();
		init_ok = 0;
		game_set_engine_error(1);
	}

	return NULL;
}
