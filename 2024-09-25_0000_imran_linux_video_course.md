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
    - [Free practice](#free-practice)
  - [`alias` - create a shortcut for a command](#alias---create-a-shortcut-for-a-command)
  - [`history` - show the history of commands](#history---show-the-history-of-commands)
- [Module 7: Networking, Services, and System Updates](#module-7-networking-services-and-system-updates)
  - [Network Files and Configuration](#network-files-and-configuration)
  - [Network Commands](#network-commands)
  - [NIC - Network Interface Card](#nic---network-interface-card)
    - [Free practice](#free-practice-1)
  - [NIC bonding](#nic-bonding)
  - [Network utilities](#network-utilities)

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
tmux a                                  # reattach to previous session
tmux ls                                 # list all sessions
Ctrl+b d                                # detach from the session

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

#### Free practice

```bash
# awk - scan every line of a file and perform an action
date | awk '{printf "DayOfWee:%s Month:%s\n", $1, $2}'

# Correct syntax of the for-loop in one line.
# Note the semicolon between do and echo is not needed.
for i in 1 2 3 4; do echo "Hello $i"; done

# exit status of the last command. 0 means success.
$?  # For this example, it will be 0 because the last command echo Hello 4 was successful.
```

### `alias` - create a shortcut for a command

```bash
alias ll='ls -l'  # create an alias for the current session
/home/user/.bashrc # file to store aliases for the current user
/etc/bash.bashrc  # file to store aliases for all users
```

### `history` - show the history of commands

```bash
~/.bash_history  # file to store the history of commands
history          # show the history of commands
!123             # execute the command with the number 123 from the history
```

## Module 7: Networking, Services, and System Updates

### Network Files and Configuration

```bash
/etc/hosts          # file to store the IP addresses of the hosts. Tiny DNS.
/etc/hostname       # file to store the hostname of the system
/etc/resolv.conf    # file to store the gateway and DNS server
```

### Network Commands

```bash
ping                # check availability of a host
ip a                # show the interfaces and their IP addresses
ip link set dev <interface> up    # enable the interface
ip link set dev <interface> down  # disable the interface
ss -tuln            # show the listening ports
tcpdump             # capture the network packets
```

### NIC - Network Interface Card

```bash
ethtool <interface>                         # show the status of the NIC
```

#### Free practice

```bash
tail -f app.log | grep -E "error|warning"   # show the errors and warnings in the log file
tail -f /var/log/syslog | grep "network"    # show the network-related logs
tail -f file1 file2 file3                   # show the logs of multiple files
```

### NIC bonding

NIC Bonding — это полезная технология для создания одного виртуального сетевого интерфейса на основе нескольких физических, что позволяет улучшить надёжность, производительность, и отказоустойчивость сети.

```bash
modprobe bonding            # load the bonding module
modinfo bonding             # show the information about the bonding module
systemctl restart network   # restart the network service
```

### Network utilities

```bash
apt install network-manager
nmcli                           # Network Manager Command Line Interface
nmtui                           # Network Manager Text User Interface
nm-connection-editor            # Network Manager GUI
```
