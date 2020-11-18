# ~/.bashrc: executed by bash(1) for non-login shells.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples

#export LANG=fr_FR.utf8

# Source global definitions
if [ -f /etc/bash.bashrc ]; then
    . /etc/bash.bashrc
    #echo "Globals sourced"
fi

# don't put duplicate lines in the history. See bash(1) for more options
#export HISTCONTROL=ignoredups

# make history really long
export HISTSIZE=20000

export HISTCONTROL=ignoreboth:erasedups   # no duplicate entries
shopt -s histappend                       # append history file
#export PROMPT_COMMAND="history -a"        # update histfile after every command
#export HISTIGNORE='&:ls:cd ~:cd ..:[bf]g:exit:h:history:ls:ll:ls -altr:ls -alt:la:l:pwd:exit:mc:su:df:clear:ps:h:history:ls -al'

# make history save and update across multiple terminals
# immediate availability in other terminals
#export PROMPT_COMMAND='history -a; history -r'
# availability of groups of commands organized per terminal
export PROMPT_COMMAND='history -a;'


# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
shopt -s checkwinsize

# make less more friendly for non-text input files, see lesspipe(1)
[ -x /usr/bin/lesspipe ] && eval "$(lesspipe)"

# Alias definitions.
# You may want to put all your additions into a separate file like
# ~/.bash_aliases, instead of adding them here directly.
# See /usr/share/doc/bash-doc/examples in the bash-doc package.

# enable color support of ls and also add handy aliases
if [ "$TERM" != "dumb" ]; then
    eval "`dircolors -b`"
    alias ls='ls --color=auto'
    alias dir='ls --color=auto --format=vertical'
    alias vdir='ls --color=auto --format=long'
    #echo "Not dumb terminal"
fi

# some more ls aliases
alias ll='ls -l'
alias la='ls -A'
alias l='ls -CF'
alias mv='mv -i'
#alias rm='mv -i \!* ~/TRASH/'
#alias rm='mv --target-directory ~/.Trash'
alias cp='cp -i'

#Added to list only directories or only files
#Another way to do it is: ls -d */
alias lf="ls -l | egrep -v '^d'"
alias ldir="ls -l | egrep '^d'"

#Added to list only directories using find
alias lsdir="find . -maxdepth 1 -type d"

# enable programmable completion features (you don't need to enable
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
# sources /etc/bash.bashrc).
if [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
fi

# set PATH so it includes user's private bin if it exists
if [ -d ~/bin ] ; then
    PATH=~/bin:"${PATH}"
fi

#PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '

#PROMPT_COMMAND='history -a;echo -en "\033[m\033[38;5;2m"$(( $(sed -nu "s/MemFree:[\t ]\+\([0-9]\+\) kB/\1/p" /proc/meminfo)/1024))"\033[38;5;22m/"$(($(sed -nu "s/MemTotal:[\t ]\+\([0-9]\+\) kB/\1/Ip" /proc/meminfo)/1024 ))MB"\t\033[m\033[38;5;55m$(< /proc/loadavg)\033[m"'
#PS1='\[\e[m\n\e[1;30m\][$$:$PPID \j:\!\[\e[1;30m\]]\[\e[0;36m\] \T \d \[\e[1;30m\][\[\e[1;34m\]\u@\H\[\e[1;30m\]:\[\e[0;37m\]${SSH_TTY} \[\e[0;32m\]+${SHLVL}\[\e[1;30m\]] \[\e[1;37m\]\w\[\e[0;37m\] \n($SHLVL:\!)\$ '

# Comment in the above and uncomment this below for a color prompt
#eval `ssh-agent -s`

# Proposé par Frédéric en 15/11/2019
# config Java 2019 pour Eclipse Neon (et modelio ?)
export JAVA_HOME=/usr/local/jdk
export PATH=$JAVA_HOME/bin:$PATH

# config POSTGRES 2019
export PGHOST=serveur-etu.polytech-lille.fr
#export PGHOST=houplin.studserv.deule.net ;
export PAGER='less -SMFX' ;

#Works fine, without gitprompt
PS1='\[\033[01;33m\]\u@\h\[\033[00m\] \[\033[01;34m\]\w\[\033[00m\] \$ '
#With gitprompt
PS1='\[\033[01;32m\]\u@\h \[\033[01;34m\]\w\[\033[01;36m\]$(__git_ps1 " (%s)") \[\033[00m\]\$ '

#~/git-prompt.sh
#export PS1='\u@\h:\w$(__git_ps1 " (%s)")\$ '
export GIT_PS1_SHOWDIRTYSTATE=1

if [ -f ~wrudamet/public/git-prompt.sh ]; then
    #echo set git prompt
    . ~wrudamet/public/git-prompt.sh
fi
