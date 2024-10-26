# Complete Linux Training Course to Get Your Dream IT Job 2024

- [Module 1: Introduction to Linux](#module-1-introduction-to-linux)
- [Module 2: Download, Install, and Configure Linux](#module-2-download-install-and-configure-linux)
- [Module 3: System Access and File System](#module-3-system-access-and-file-system)
- [Module 4: Linux Fundamentals](#module-4-linux-fundamentals)
- [Module 5: System Administration](#module-5-system-administration)
  - [`screen` - split terminal windows](#screen---split-terminal-windows)
    - [Troubleshooting](#troubleshooting)
  - [`tmux` - terminal multiplexer (modern alternative to `screen`)](#tmux---terminal-multiplexer-modern-alternative-to-screen)
- [Module 6: Shell Scripting](#module-6-shell-scripting)
  - [What is Linux Kernel](#what-is-linux-kernel)
  - [What is Shell Scripting](#what-is-shell-scripting)

## Module 1: Introduction to Linux

## Module 2: Download, Install, and Configure Linux

## Module 3: System Access and File System

## Module 4: Linux Fundamentals

## Module 5: System Administration

### `screen` - split terminal windows

- Allow you to split terminal windows
- Save the state of the terminal between sessions. So you can detach and reattach the terminal session even after you close the terminal.

```
screen                      # start a new session
screen -S session_name      # start a new session with a name
screen -ls                  # list all sessions
screen -r session_name      # reattach
Ctrl+a d                    # detach from the session

Ctrl+a c                    # create a new window (tab)
Ctrl+a n                    # switch to the next window
Ctrl+a p                    # switch to the previous window
Ctrl+a "                    # list all windows
Ctrl+a A                    # rename the current window

Ctrl+a |                    # split the window vertically
Ctrl+a S                    # split the window horizontally
Ctrl+a tab                  # switch between splits
```

#### Troubleshooting

```
Ctrl+a s                    # lead to freeze the terminal
Ctrl+a q                    # unfreeze the terminal
```

### `tmux` - terminal multiplexer (modern alternative to `screen`)

```
tmux                                    # start a new session
tmux new -s session_name                # start a new session with a name
tmux kill-session -t session_name       # kill a session

Ctrl+b d                    # detach from the session
tmux ls                     # list all sessions
tmux a                      # reattach to previous session

Ctrl+b c                    # create a new window (tab - not a split)
Ctrl+b ,                    # rename the current window
Ctrl+d                      # close the current window

Ctrl+b n                    # switch to the next window
Ctrl+b p                    # switch to the previous window
Ctrl+b w                    # list all windows

Ctrl+b %                    # split the window vertically
Ctrl+b <arrow>              # switch between splits
Ctrl+b "                    # split the window horizontally
```

## Module 6: Shell Scripting

### What is Linux Kernel

- **Hardware**.
- Linux **Kernel** is an interface between user and hardware.
- Kernel gets commands from the **shell** (GUI or CLI) and sends them to the hardware.
  - Gnome, KDE, etc. are GUI shells.
  - sh, bash, zsh, etc. are CLI shells.
  - tcsh, csh - shells for C++ developers.
  - ksh - compatible with sh and bash.

### What is Shell Scripting

- `#!/bin/bash` - shebang line
- script should be executable: `chmod +x script.sh`
- Script has to called from absolute path: `/path/to/script.sh`
- Script can be called from relative path: `./script.sh`

```bash
a=`hostname` # execute the command and store the output in a variable
```
