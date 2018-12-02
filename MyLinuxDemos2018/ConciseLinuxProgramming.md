﻿# Linux程序设计
**History**
|version|date|description|
|-|-|-|
|1.0|181128| |

--------------
**Content**     
* Linux常用命令
* Shell编程
* C语言开发工具
    * gcc编译器
    * make工程文件
* Linux系统函数
* 文件IO操作
* 进程控制
* 进程通信
* 线程
* 网络变编程
    * TCP/IP
    * socket变成
* 图形编程
* 设备驱动程序设计
---
# X. Linux常用命令
### 命令的执行
```
顺序执行:
    command1; command2
并发执行:
    command1&command2&
AND条件执行:
    command1&&command2&&command3    
    &&是AND操作符号.执行到一个false为止，其后command不再执行
OR条件执行:
    command1||command2||command3
    ||是OR操作符号。执行到一个true为止，其后command不再执行

sample:
    #ls sample || touch sample && echo "file created ok"
    先执行ls sample，若sample不存在则touch sample创建并输出"file created ok"
```
### **ls, 列出文件清单**  
```
 format:
    ls [parameter] [filename]  
 parameter:  
    -a, 列出所有文件
    -l, 长格式输出
    -R, 递归列出子目录下的文件
    -L, 列出文件的链接名link
    -S, 以文件大小进行排序
```
ls结果字段说明
```
字段1,    第1个字母表示文件类型，
            -, normal
            b, block device 
            c, character device
            d, directory
            l, symbol link
            p, FIFO 
            s, socket
          其他9个字母分3组，3组分别表示owner, group, and other
            r, read
            w, write
            x, execute
            -, none 
字段2,    文件连接数
字段3,    owner's login name          
字段4,    group name
字段5,    size in bytes
字段6,7,8,    最近一次修改的日期时间
字段9,    文件名
```
### **mkdir，创建目录**
```
format:
    mkdir [para] [directoryName]
paramter:
    -m  设定权限

sample:
    mkdir -m 777 tsk

```
### **rmdir, 删除目录**
```
format:
    rmdir directoryName
```

### **cd, 切换当前目录**
```
format:
    cd directoryName
```

### **mv, 移动文件或目录**
```
format:
    mv srcFileName  targetFileName
```    

### **cp, 复制文件或目录**
```
format:
    cp srcFileName targetFileName

```

### **rm, 删除文件或目录**
```
format:
    rm [para] fileName
parameter:
    -r, 递归删除子目录及其下文件
    -f, 不输出提示信息    
```
### **grep, 搜索文件中的特定内容，并将含有这些内容的行输出到标准输出**
```
format:
    grep [para] [fileName]
param:
    -v, 显示不含匹配文本的所有行
    -n, 显示匹配行及行号
sample:
    搜索当前目录的所有文件内容，显示含有kkk的行及行号。
    grep -n kkk *.*        
```
### **find, 在目录中搜索文件**
```
format:
    find [path] [param] [fileName]
    find   path   -option   [   -print ]   [ -exec   -ok   command ]   {} \;
param:
    -name,  按照文件名查找
    -user,  按照文档属主查找
    -print： find命令将匹配的文件输出到标准输出。
    -exec： find命令对匹配的文件执行该参数所给出的shell命令。相应命令的形式为'command' { } \;，注意{ }和\；之间的空格。
    -ok： 和-exec的作用相同，只不过以一种更为安全的模式来执行该参数所给出的shell命令，在执行每一个命令之前，都会给出提示，让用户来确定是否执行。    
sample:
    找出/home目录下'zb'用户的文件
    find /home -user zb
    -name   filename             #查找名为filename的文件
    -perm                        #按执行权限来查找
    -user    username             #按文件属主来查找
    -group groupname            #按组来查找
    -mtime   -n +n                #按文件更改时间来查找文件，-n指n天以内，+n指n天以前
    -atime    -n +n               #按文件访问时间来查GIN: 0px">

    -ctime    -n +n              #按文件创建时间来查找文件，-n指n天以内，+n指n天以前

    -nogroup                     #查无有效属组的文件，即文件的属组在/etc/groups中不存在
    -nouser                     #查无有效属主的文件，即文件的属主在/etc/passwd中不存
    -newer   f1 !f2              找文件，-n指n天以内，+n指n天以前 
    -ctime    -n +n               #按文件创建时间来查找文件，-n指n天以内，+n指n天以前 
    -nogroup                     #查无有效属组的文件，即文件的属组在/etc/groups中不存在
    -nouser                      #查无有效属主的文件，即文件的属主在/etc/passwd中不存
    -newer   f1 !f2               #查更改时间比f1新但比f2旧的文件
    -type    b/d/c/p/l/f         #查是块设备、目录、字符设备、管道、符号链接、普通文件
    -size      n[c]               #查长度为n块[或n字节]的文件
    -depth                       #使查找在进入子目录前先行查找完本目录
    -fstype                     #查更改时间比f1新但比f2旧的文件
    -type    b/d/c/p/l/f         #查是块设备、目录、字符设备、管道、符号链接、普通文件
    -size      n[c]               #查长度为n块[或n字节]的文件
    -depth                       #使查找在进入子目录前先行查找完本目录
    -fstype                      #查位于某一类型文件系统中的文件，这些文件系统类型通常可 在/etc/fstab中找到
    -mount                       #查文件时不跨越文件系统mount点
    -follow                      #如果遇到符号链接文件，就跟踪链接所指的文件
    -cpio                %;      #查位于某一类型文件系统中的文件，这些文件系统类型通常可 在/etc/fstab中找到
    -mount                       #查文件时不跨越文件系统mount点
    -follow                      #如果遇到符号链接文件，就跟踪链接所指的文件
    -cpio                        #对匹配的文件使用cpio命令，将他们备份到磁带设备中
    -prune                       #忽略某个目录
sample:

    $find   ~   -name   "*.txt"   -print    #在$HOME中查.txt文件并显示
    $find   .    -name   "*.txt"   -print
    $find   .    -name   "[A-Z]*"   -print   #查以大写字母开头的文件
    $find   /etc   -name   "host*"   -print #查以host开头的文件
    $find   .   -name   "[a-z][a-z][0–9][0–9].txt"    -print   #查以两个小写字母和两个数字开头的txt文件
    $find .   -perm   755   -print
    $find   .   -perm -007   -exec ls -l {} \;   #查所有用户都可读写执行的文件同-perm 777
    $find   . -type d   -print
    $find   .   !   -type   d   -print 
    $find   .   -type l   -print

    $find   .   -size   +1000000c   -print        #查长度大于1Mb的文件
    $find   .   -size   100c         -print       # 查长度为100c的文件
    $find   .   -size   +10   -print              #查长度超过期作废10块的文件（1块=512字节）

    $cd /
    $find   etc   home   apps    -depth   -print   | cpio   -ivcdC65536   -o   /dev/rmt0
    $find   /etc -name "passwd*"   -exec grep   "cnscn"   {}   \;   #看是否存在cnscn用户
    $find . -name "yao*"   | xargs file
    $find   . -name "yao*"   |   xargs   echo    "" > /tmp/core.log
    $find   . -name "yao*"   | xargs   chmod   o-w

    find   -name april*                     在当前目录下查找以april开始的文件
    find   -name   april*   fprint file        在当前目录下查找以april开始的文件，并把结果输出到file中
    find   -name ap* -o -name may*   查找以ap或may开头的文件
    find   /mnt   -name tom.txt   -ftype vfat   在/mnt下查找名称为tom.txt且文件系统类型为vfat的文件
    find   /mnt   -name t.txt ! -ftype vfat   在/mnt下查找名称为tom.txt且文件系统类型不为vfat的文件
    find   /tmp   -name wa* -type l            在/tmp下查找名为wa开头且类型为符号链接的文件
    find   /home   -mtime   -2                 在/home下查最近两天内改动过的文件
    find /home    -atime -1                  查1天之内被存取过的文件
    find /home -mmin    +60                  在/home下查60分钟前改动过的文件
    find /home   -amin   +30                  查最近30分钟前被存取过的文件
    find /home   -newer   tmp.txt             在/home下查更新时间比tmp.txt近的文件或目录
    find /home   -anewer   tmp.txt            在/home下查存取时间比tmp.txt近的文件或目录
    find   /home   -used   -2                  列出文件或目录被改动过之后，在2日内被存取过的文件或目录
    find   /home   -user cnscn                列出/home目录内属于用户cnscn的文件或目录
    find   /home   -uid   +501                  列出/home目录内用户的识别码大于501的文件或目录
    find   /home   -group   cnscn              列出/home内组为cnscn的文件或目录
    find   /home   -gid 501                   列出/home内组id为501的文件或目录
    find   /home   -nouser                    列出/home内不属于本地用户的文件或目录
    find   /home   -nogroup                   列出/home内不属于本地组的文件或目录
    find   /home    -name tmp.txt    -maxdepth   4   列出/home内的tmp.txt 查时深度最多为3层
    find   /home   -name tmp.txt   -mindepth   3   从第2层开始查
    find   /home   -empty                     查找大小为0的文件或空目录
    find   /home   -size   +512k                查大于512k的文件
    find   /home   -size   -512k               查小于512k的文件
    find   /home   -links   +2                查硬连接数大于2的文件或目录
    find   /home   -perm   0700                查权限为700的文件或目录
    find   /tmp   -name tmp.txt   -exec cat {} \;
    find   /tmp   -name   tmp.txt   -ok   rm {} \;

    find    /   -amin    -10     # 查找在系统中最后10分钟访问的文件
    find    /   -atime   -2        # 查找在系统中最后48小时访问的文件
    find    /   -empty             # 查找在系统中为空的文件或者文件夹
    find    /   -group   cat        # 查找在系统中属于 groupcat的文件
    find    /   -mmin   -5         # 查找在系统中最后5分钟里修改过的文件
    find    /   -mtime   -1       #查找在系统中最后24小时里修改过的文件
    find    /   -nouser           #查找在系统中属于作废用户的文件
    find    /   -user    fred     #查找在系统中属于FRED这个用户的文件


    查当前目录下的所有普通文件，并在- e x e c选项中使用ls -l命令将它们列出
    #find . -type f -exec ls -l {} \; 
    -rw-r–r–    1 root      root         34928 2003-02-25   ./conf/httpd.conf 
    -rw-r–r–    1 root      root         12959 2003-02-25   ./conf/magic 
    -rw-r–r–    1 root      root          180 2003-02-25   ./conf.d/README 

    在/ l o g s目录中查找更改时间在5日以前的文件并删除它们：
    #find logs -type f -mtime +5 -exec   -ok   rm {} \;

    比如要查找磁盘中大于3M的文件：
    #find . -size +3000k -exec ls -ld {} ;
```
### **head, 查看文件开始**
```
sample
    文件的前5行
    head -5 file.txt
    文件的前5个字节
    head -c 5 file.txt
```

### **tail, 显示文件的末尾**
```
param:
    +n, 显示正数n行开始的所有行
    -n, 显示倒数n行开始的所有行
```

### **wc, 统计文件的行数，单词数等**
```
param:
    -c, 统计字节数
    -m, 字符数
    -l, 行数
    -w, 单词数
sample
    wc -l -c liua
```

### **gzip, 压缩和解压文件**
```
param:
    -d, 解压
```

### **tar, 备份**
```
format:
    tar [param]  fileName
param:
    -c, 压缩
    -x, 解压    
    -z, 使用gzip
    -v, verbose
    -j, 使用bzip2
    -f, 文件
sample:
    tar -zxvf home.tar.gz

```    

### **mount,umount,挂载和卸载文件系统**
```
foramt:
    mount [-t vfstype] [-o options] device dir
    umount dir
param
    -t vfstype,   文件系统类型
    -o options,   挂载方式
                    loop
                    ro
                    rw
                    iocharset
```

### **useradd, 建立用户账户并创建用户目录**
```
format:
    useradd userName
desc:
    随后应及时建立用户密码，使用passwd命令    
```

### **passwd, 修改用户的登录密码**
```
format:
    passwd accountName
```

### **kill, 终止进程**
```
sample:
    kill -9 1752
```

### **date, 显示和设置当前时间和日期**    

### net-tools和iproute2
|net-tools|iproute2|
|-|-|
|arp -na|ip neigh|
|ifconfig|ip link|
|ifconfig -a|ip addr show|
|ifconfig --help|ip help|
|ifconfig -s|ip -s link|
|ifconfig eth0 up|ip link set eth0 up|
|ipmaddr|ip maddr|
|iptunnel|ip tunnel|
|netstat|ss|
|netstat -e|ip -s link|
|netstat -g|ip maddr|
|netstat -l|ss -l|
|netstat -r|ip route|
|route add|ip route add|
|route del|ip route del|
|route -n|ip route show|
|vconfig|ip link|

### **ifconfig, 查看和更改网络接口的地址和参数， 包括IP, netmask, broadcast addr**
该命令已obsolete. 使用ip命令.
```
format:
    ifconfig <interface> [IP netmask maskCode] <up|down>
sample:
    ifconfig eth0 192.168.1.15 netmask 255.255.255.68 broadcast 192.168.1.158 up

```

### **ifup/ifdown, 激活和关闭网络适配卡**
```
format
    ifup <interface>
    ifdown <interface>
```

### **ping**

### **netstat, 检查网络状态**
```
format
    netstat [para]
param:
    -r, 显示routing table
    -r, 显示所有连线中的socket    
```

### **arp, 确定IP对应的物理地址**
```
format:
    arp [para]
param
    -a IP，  显示所有与该接口相关的arp缓存项目
    -e, 显示系统默认的缓存情况    
```

### **su, 变更为其他使用者的身份**
```
format:
    su [param] user
param:
    -c command,  以user身份执行命令command,执行完毕后复原身份。
    --login,  类似以user身份登录，包括转变home dir,环境变量等。
```

### **chmod, 改变文件或目录的访问权限**
```
format:
    chmod [param]   <file|dir>    
param:
    who(u,g,o,a),   user, group, owner, all, 默认a
    =, +, -,        设置为, 增加，减去
sample:
    chmod u=rwx file
    chmod ug+w,o-w file1.txt file2.txt
```

### **chown, 更改文件或目录的属主和属组**
```
format:
    chown [param] <file|dir>
param:
```

### **ps, 显示进程信息**
```
format:
    ps [option]
param:
    -m, 内存信息
    -w，加宽显示
    -a，所有用户信息
    -u，按用户名和启动时间顺序显示进程
    -x，显示无控制终端的进程
    -l，以长列表的形式显示
字段释义:
    USER,   user name, 进程执行者的用户名
    UID,    user id number, 进程执行者的id
    PID,    process id, 进程id
    PPID,   parent process id, 父进程id
    VSZ,    total VM size in KiB
    RSS,    resident set size,驻留集的大小
    F,      flags as in long format F field
            1  forked but didn't exec
            4  used super-user privileges
    WCHAN,
    STAT,   state of a process
            D   uninterruptible sleep(usually IO)
            I   idle kernel thread
            R   running or runnable(on run queue)
            S   interruptible sleep(waiting for an event)
            T   stopped by job control sigbal
            t   stopped by debugger during the tracing
            W   paging(not valid since the 2.6 kernel)
            X   dead(should never be seen)
            Z   defunct("zombie")process, terminated but not reaped by its parent            
    TTY,    the device number of the controlling tty
    %CPU,   cpu utilization
    %MEM,   mem占用比例
    START,  time process was started
    TIME,   user time
    COMMAND,    命令名
```
### **who, 显示系统中的登录用户**
```
format:
    who [option]
option:
    -u, 不显示使用者的动作/工作
    -s, 简短格式    
param:
```

### **top, 进程实时监视命令**
### **free, 显示物理内存**
### **kill, 进程终止命令**
```
format:
    kill [-signal] <PID|name>
option:
    signal，    1   SIGHUP,  term
                2   SIGINT， ctrl+c
                3   SIGQUIT, ctrl+\
                9   SIGKILL, kill signal
                15  SIGTERM, termination signal(defualt)
```
### **echo, 显示字符串**
```
format:
    echo [option] [string]
option:
    -E, 不解析转义字符
    -e, 解析转义字符
    \33[???,    控制序列, \33是ESC的ascii，具体参见https://en.wikipedia.org/wiki/ANSI_escape_code    
```

# X. Shell编程
仅总结BASH shell的编程。
## 环境变量
修改环境变量可以在初始化文件/etc/profile和/etc/csh.cshrc中进行修改。  
部分bash环境变量
* CDPATH, cd命令访问的目录别名
* EDITOR, 默认editor
* ENV,  linux查找配置文件的路径
* HOME, 主目录
* PATH,
* PS1, 提示符
* PS2, 二级提示符
* PWD, 当前工作目录
* TERM, 当前控制台终端类型
## shell中的元字符metacharacters
* 换行符, 命令后应有换行符。
* 空格,  命令行中的分隔符。
* TAB,   命令行中的分隔符。
* #,    注释行的起首字符
* ",    字符串，并允许替换
* ',    字符串，括号中字符按原义解释
* $,    一行的结束, 或引用变量
* &,    后台执行命令
* ()    在子shell中执行命令
* []    匹配[]中一个字符
* {}    在当前shell中执行命令，或实现扩展
* \*     匹配0个或多个字符
* ?      匹配1个字符
* ^     紧跟^后面字符开始的行，或作为否定符号
* `     替换命令
* |     管道命令
* ;     顺序执行命令的分隔符
* <     输入重定向符号
* >     输出重定向符号
* /     根目录或路径名分隔符
* \     转义符
* !     启动历史记录列表中的命令和当前命令
* %     作业号的起首字符
* ~     主目录(HOME)

```
大括号扩展sample:
    #echo chap_{1,2,3}.txt 
    chap_1.txt chap_2.txt chap_3.txt
    #mkdir dir{A,B,C,D}
    #ls -F
    dirA/ dirB/ dirC/ dirD/
```

## shell脚本文件
脚本第一行通常可以指定执行脚本文件的程序，例如下面是一个脚本文件的内容，
```
#!/bin/sh
echo "Mr.$USER, Today is:"
echo &date "+%B%d%A"
echo "Wish you a lucky day!"
```
## shell的位置参数和变量
### 位置参数
|位置参数|说明|读写特性|
|-|-|-|
|$0|shell脚本的文件名字|readonly|
|$1-$9|命令行参数1-9的值 |ro|
|$*|命令行中所有的参数。若 \$\*被引号""包括，即"\$\*",指各参数之间用环境变量IFS中的第一个字符分隔开|ro |
|$@ |命令行中所有的参数。若 \$\*被引号""包括，即"\$\*",但各参数之间不使用环境变量IFS中的第一个字符分隔开 |ro |
|$# |命令行参数的总个数 |ro |
|$$ |shell脚本进程的id号 |ro |
|$? |最近一次命令的退出状态 |ro |
|$! |最近一次后台进程的id号 |ro |

### shift
参数超过9个时，可以使用shift命令左移参数得到后面位置的参数
```
format:
    shift [N]
```

### set
设置位置参数
```
format:
    set [options] argument-list
    将argument-list中的内容设置到$N中。
```

## 变量
shell中访问变量的内容，即右值访问使用$符号前缀变量名，赋值时，即左值访问时，直接使用变量名。
### 变量的声明
Bash并不必须要声明变量，但有些特殊类型的变量必须要声明。一个变量Bash默认是一个字符串，除非明确声明指定。
```
format:
    declare [options] [name[=value]]
    typeset [options] [name[=value]]
options:
    -a,     是数组类型
    -f,     是函数    
    -i,     是整数类型
    -r,     是只读变量
    -x,     全局变量，变量可以被子进程访问

sample:
    #declare -i age=20
    #declare -rx OS=LINUX
    #echo $age
    #echo $OS    
```
### 变量的赋值

```
format:
    variable=value
    等号前后没有空格，若需要空格，使用双引号括起来。
```
### 变量单引号和双引号引用
双引号中，字符$,`和\做特殊符号，其他字符按字面义解释。双引号中的$字符前缀的变量名将做右值替换。  
而单引号中$变量名不做右值替换，并且所有字符都按字面意思处理。
```
sample:
    #BOOK="linux book"
    #echo $BOOK
    linux book
    #MSG=`$BOOK`
    #echo $MSG
    $BOOK

```
### 命令替换
形如$(command)或\`command`的命令将被替换为命令的输出结果。
```
sample:
    #pwd
    /root/mydir
    #cmd1=pwd
    #echo "$cmd1"
    pwd
    #cmd1=$(pwd)
    #echo "$cmd1"
    /root/mydir
```
### 变量的输入
read命令将用户的输入赋值给一个shell变量。
```
format:
    read [options] variable-list
options:
    -a name     把词读入name数组中
    -e          把一整行读入第一个变量中，其他变量均为null
    -n          echo输出命令字符串后，光标仍停留在同一行
    -p prompt   如果是从终端读入数据则显示prompt字符串    
```
### 控制结构语句
```
if-sentence1:
    if expression
        then
        then-command
    fi
if-sentence2:
    if expression
        then
        command-list
    else
        command-list
    fi
if-sentence3:
    if expression1
        then
        then1-commands
    elif expression2
        then
        then2-commands
    elif expression3
        then
        then3-commands
    ...
    else
        else-commands
    fi    
```

if中的expression使用的格式如下.
```    
    test [expression]
    ,or
    [[expression]]
```
上面的expression测试可以使用下面表中的比较。

|字符串比较|结果|
|-|-|
|str1=str2 | 相同则为真|
|str1!=str2| |
| -n string| 不为空则为真|
| -z string| 为空则为真|

|算数比较|结果|
|-|-|
|exp1 -eq exp2 |相等则为真 |
|exp1 -ne exp2 | |
|exp1 -gt exp2 | |
|exp1 -ge exp2 | |
|exp1 -lt exp2 | |
|exp1 -le exp2 | |
|!exp |布尔取反 |

|文件测试|结果|
|-|-|
|-d file| 是目录则为真|
|-e file| 文件存在则真|
|-f file| 常规文件则真|
|-g file|文件的SGID位被设置则真|
|-r file|可读则真|
|-s file|长度不为0则真|
|-u file|文件SUID位被设置则真|
|-w file|文件可写则真|
|-x file|文件可执行则真|


```
for-sentence:
    for variable [in argument-list]
    do
    command-list
    done

sample:
    for foo in bar bie 123 four five 888
    do
    echo "$foo"
    done

```

```
while-sentence:
    while expression
    do
    command-list
    done

until-sentence
    until expression
    do
    command-list
    done

case-sentence:
    case variable in
    pattern1) command-list1
        ;;
    pattern2) command-list2
        ;;
    ...
    pattern3) command-listN
        ;;
    esac        
```
### 其他语句
```
break-sentence:
    break
continue-sentence:
    continue
exit-sentence:
    exit n
    退出码n， 0成功，1-125脚本使用，126文件不可执行，127命令未找到，128及以上有信号发生。
printf-sentence:
    printf "format-string" parameter-list
        
```

### 数值处理命令，let, $((expression)), 和expr
```
format:
    let expression-list
    
    $((expression))
    在expression中的变量名称不需要加$

    expr args

sample:
    let x=6 y=9
    let t=x+y
    $((100-x))    
    x=`expr $x+1`

数值运算符:
    | & = > >= < <= != + - * / %    
    注意 expr表达式中的元字符做运算符使用时需要使用转义符。
    a1=$(expr $a1 \* $a1)
```
### 数组
下标由0开始。
```
三种声明方法。
直接赋值使用，
    array[key]=value
声明1，
    array=(value1 value2 value3...)
声明2,
    array=([1]=one [2]=two [3]=three...)
```

```
访问元素
    ${array[key]}
删除元素
    unset array[1]
删除数组
    unset aray        

元素个数
    ${#array[*]}    
    ,or
    ${#array[@]}
    
    特别注意, 双引号形式
        "${array[@]}"是将原数组的内容逐个复制到新数组，生成一个一样的新数组。
        "${array[*]}"是将原数组中的所有元素当成一个元素复制到新数组。
子串提取
    ${array[*|@]:N:M}    
    N是开始下标，M是结束下标
```
```    
字串删除
    ${array[@|*]<op><pattern>}
    op:
        #,  从左边开始最短的匹配
        \##,  从左边开始最短的匹配
        %,  从右边开始最短的匹配
        %%,  从右边开始最短的匹配
sample:
    array=(one two three four)
    ${array[@]#t*e}        删除从左边开始最短的匹配't*e',即thre
    ${array[@]##t*e}        删除从左边开始最长的匹配't*e',即three
   
```

```
子串替换
    ${array[@|*]/<pattern1>/<str>}
    替换第一个匹配到的字串为str

    ${array[@|*]//<pattern1>/<str>}
    替换所有匹配到的字串为str

```
### 几个例子
```
#!/bin/bash
while :
do
    echo -n "输入 1 到 5 之间的数字:"
    read aNum
    case $aNum in
        1|2|3|4|5) echo "你输入的数字为 $aNum!"
        ;;
        *) echo "你输入的数字不是 1 到 5 之间的! 游戏结束"
            break
        ;;
    esac
done
```

```
#!/bin/sh
#定义方法一 数组定义为空格分割
arrayWen=(a b c d e f)
#定义方法二
arrayXue[0]="m"
arrayXue[1]="n"
arrayXue[2]="o"
arrayXue[3]="p"
arrayXue[4]="q"
arrayXue[5]="r"
#打印数组长度
echo ${#arrayWen[@]}
#for 循环遍历 
for var in ${arrayWen[@]};
do
    echo $var
done
#while循环遍历
i=0
while [[ i -lt ${#arrayXue[@]} ]]; do
    echo ${arrayXue[i]}
    let i++
done
```

```
#实现展示进度百分比的实现方法
# 定义变量 i
i=1
 
# 获取 3.log 这个文件的行数，并把运行结果赋予变量 l
l=$(wc -l 3.log | sed 's/^[ \t]*//g' | cut -d ' ' -f1)
 
# 每行遍历循环
while read line; do
 
 # 输出百分比
 echo -en "\b\b\b\b"`echo $i*100/$l | bc `'%'
 
 # 计算 i++
 ((i++))
 
# 传入 3.log 这个要处理的文件
done < 3.log
# 完成时打个OK，因为字符长度不足以遮盖原先的百分比，所以后面加了几个空格
echo -e '\b\b\b\bOK   '
```

## 函数
### 函数的定义
```
format:
    funciton_name()
    {
        command-list
    }
```
当函数被调用时，脚本位置参数$*, $@, $#, $1-9等会被替换为函数的参数。当函数执行完毕后，这些位置参数恢复为先前的值。
可以使用local关键字声明局部变量。
可以使用return命令返回数字值。
### 函数的调用
```
format:
    function_name  [args]
```


# X. C语言开发工具


## XX. gcc编译器
### gcc编译流程
* preprocessing, output *.i
* compiling, output *.s
* assembling, output *.o
* linking, output exe file
### gcc的参数

一般参数
```
    -c      编译但不链接，生成obj
    -S      编译但不汇编，生成汇编代码
    -E      仅预编译，生成*.i文件
    -g      执行代码中嵌入调试信息
    -o file 指定输出文件名
    -v      gcc版本信息
    -I dir  头文件的搜索路径中增加dir目录
    -L dir  库文件的搜索路径中增加dir目录
    -static 静态链接库
    -llibrary   链接名为library的库文件。 即-lmyname将会寻找myname, myname.so, libmyname.so, libmyname这样的库文件.
    -On     n=0,1,2,3,s  0优化最低，3最高，推荐2
```

告警和出错参数
```
    -ansi       ansi标准
    -pedantic   允许发出ansi c标准的所有warning信息
    -pedantic-error 允许发出ansi c标准的所有error信息
    -w          关闭所有warning
    -Wall       允许所有warning
    -werror     warning视作error，即停止编译。
```

### 库
静态库名lib\*.a形式，动态库名lib\*.so形式.
## XX. make工程文件
### make文件的规则
```
format:
    目标文件列表:依赖文件列表
        <TAB>命令文件列表

```
### make中的变量
```
变量定义:
    VARNAME=string
变量右值:
    ${VARNAME}    
常见自动变量:
    $@      目标文件的完整名称
    $*      不含扩展名的目标文件名
    $+      以空格分开的所有依赖文件名
    $<      第一个依赖文件的名称
    $?      所有时间戳比目标文件晚的依赖文件名，以空格分开
    $^      所有不重复的依赖文件，以空格分开
    $%      目标的归档成员名称
```

## XX. gdb工具

# X. Linux系统函数
## XX. 数学函数
```
    double pow(double x, double y);
    double sqrt(double x);
    double exp(double x);           
         base-e exponential function
    double exp10(double x);
        exp10, exp10f, exp10l - base-10 exponential function 
    double log10(double x);
        base-10 logarithmic function 
    double log(double x);
        natural logarithmic function 
    int rand(void);
        eturns a pseudo-random integer in the range 0 to RAND_MAX inclusive (i.e., the mathematical range [0, RAND_MAX]). 
    void srand(unsigned int seed);        
        sets its argument as the seed for a new sequence of pseudo-random integers to be returned by rand(). 
```
## XX. 字符函数
```
    isalnum
    isalpha
    isascii
    iscntrl
    isdigit
    islower
    isprint
    isspace
    isunct
    isupper
    isxdigit
```
## XX. 时间和日期函数

```
    时间转换为字串
        char *asctime(const struct tm *tm);
        char *ctime(const time_t *timep);
    不同结构之间的转换
        struct tm *gmtime(const time_t *timep);
        struct tm *localtime(const time_t *timep);
        time_t mktime(struct tm *tm);

    取得当前时间
        int gettimeofday(struct timeval *tv, struct timezone *tz);
        int settimeofday(const struct timeval *tv, const struct timezone *tz)
```

关于time的几个重要结构
tm称作broken-down time，即分解为年月日时分秒等字段
time_t则是一个整型，代表的是秒数。
```
time_t which represents calendar time. When interpreted as an absolute time value, it represents the number of seconds elapsed since the Epoch, 1970-01-01 00:00:00 +0000 (UTC). 

struct tm {
    int tm_sec;         /* seconds */
    int tm_min;         /* minutes */
    int tm_hour;        /* hours */
    int tm_mday;        /* day of the month */
    int tm_mon;         /* month */
    int tm_year;        /* year */
    int tm_wday;        /* day of the week */
    int tm_yday;        /* day in the year */
    int tm_isdst;       /* daylight saving time */
};

struct timeval {
    time_t      tv_sec;     /* seconds */
    suseconds_t tv_usec;    /* microseconds */
};

struct timezone {
    int tz_minuteswest;     /* minutes west of Greenwich */
    int tz_dsttime;         /* type of DST correction */
};

```

## XX. 环境函数

```
char *getenv(const char *name);
    get an environment variable

int putenv(char *string);
    change or add an environment variable

int setenv(const char *name, const char *value, int overwrite);
    change or add an environment variable.

int unsetenv(const char *name);
     delete the variable name from the environment. 
```

## XX. 内存函数
```
int getpagesize(void);
    get memory page size 

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);

void *mmap(void *addr, size_t length， int prot, int flags ,
           int fd, off_t offset);
    Map files or devices into memory       
    The prot argument describes the desired memory protection of the mapping (and must not conflict with the open mode of the file). It is either PROT_NONE or the bitwise OR of one or more of the following flags:
        PROT_EXEC
            Pages may be executed. 
        PROT_READ
            Pages may be read. 
        PROT_WRITE
            Pages may be written. 
        PROT_NONE
            Pages may not be accessed.
    The flags argument determines whether updates to the mapping are visible to other processes mapping the same region, and whether updates are carried through to the underlying file. This behavior is determined by including exactly one of the following values in flags:
        MAP_SHARED
            Share this mapping. Updates to the mapping are visible to other processes that map this file, and are carried through to the underlying file. The file may not actually be updated until msync(2) or munmap() is called. 
        MAP_PRIVATE
            Create a private copy-on-write mapping. Updates to the mapping are not visible to other processes mapping the same file, and are not carried through to the underlying file. It is unspecified whether changes made to the file after the mmap() call are visible in the mapped region.
        MAP_FIXED
            Don't interpret addr as a hint: place the mapping at exactly that address. addr must be a multiple of the page size. If the memory region specified by addr and len overlaps pages of any existing mapping(s), then the overlapped part of the existing mapping(s) will be discarded. If the specified address cannot be used, mmap() will fail. Because requiring a fixed address for a mapping is less portable, the use of this option is discouraged.       
        MAP_ANONYMOUS
            The mapping is not backed by any file; its contents are initialized to zero. The fd and offset arguments are ignored; however, some implementations require fd to be -1 if MAP_ANONYMOUS (or MAP_ANON) is specified, and portable applications should ensure this. The use of MAP_ANONYMOUS in conjunction with MAP_SHARED is only supported on Linux since kernel 2.4.               

int munmap(void *addr, size_t length);
    unmap files or devices into memory.

int msync(void *addr, size_t length, int flags); 
    synchronize a file with a memory map.
    The flags argument may have the bits MS_ASYNC, MS_SYNC, and MS_INVALIDATE set, but not both MS_ASYNC and MS_SYNC. 
        MS_ASYNC specifies that an update be scheduled, but the call returns immediately. 
        MS_SYNC asks for an update and waits for it to complete. 
        MS_INVALIDATE asks to invalidate other mappings of the same file (so that they can be updated with the fresh values just written). 
            

```
mmap的详细说明  
mmap() creates a new mapping in the virtual address space of the calling process. The starting address for the new mapping is specified in addr. The length argument specifies the length of the mapping.

If addr is NULL, then the kernel chooses the address at which to create the mapping; this is the most portable method of creating a new mapping. If addr is not NULL, then the kernel takes it as a hint about where to place the mapping; on Linux, the mapping will be created at a nearby page boundary. The address of the new mapping is returned as the result of the call. 

## XX. 查找和排序函数
```
bsearch()
lfind()/lsearch()
qsort()
```

# X. 文件IO操作
## 文件的一般操作
```
int chmod(const char *path, mode_t mode);
    change mode of a file.
    mode
        S_I<R|W|X><USR|GRP|OTH>
        例如 S_IRUSER, S_IXOTH

mode_t umask(mode_t cmask);
    set and get the file mode creation mask.

int stat(const char *restrict path, struct stat *restrict buf);
int fstat(int fildes, struct stat *buf);
int lstat(const char *restrict path, struct stat *restrict buf);    
    get file status 

```
## 不带缓存的文件IO操作
```
int creat(const char *path, mode_t mode);
int open(const char *path, int oflag, ...);
int openat(int fd, const char *path, int oflag, ...);
    oflag:
        O_EXEC        Open for execute only (non-directory files). The result is unspecified if this flag is applied to a directory.
        O_RDONLY      Open for reading only.
        O_WRONLY      Open for writing only.        
        O_RDWR        Open for reading and writing. The result is undefined if this flag is applied to a FIFO.

        O_SEARCH      Open directory for search only. The result is                     unspecified if this flag is applied to a non-directory  file.        
        O_APPEND      If set, the file offset shall be set to the end of the file prior to each write.
        O_CREAT       If the file exists, this flag has no effect except as noted under O_EXCL below. Otherwise, the file shall be created;
        O_EXCL        If O_CREAT and O_EXCL are set, open() shall fail if the file exists.        
        O_SYNC        Write I/O operations on the file descriptor shall complete as defined by synchronized I/O file integrity completion.       
        O_NONBLOCK,  非阻塞操作.
int close(int fildes);         

ssize_t read(int fildes, void *buf, size_t nbyte);
ssize_t write(int fildes, const void *buf, size_t nbyte);

off_t lseek(int fildes, off_t offset, int whence);
    whence,  SEEK_SET, SEEK_CUR, and SEEK_END.

int fcntl(int fildes, int cmd, ...);
    file control

```

## 带缓存的文件IO操作
```
fopen
fclose
fgetc           读取一个字符
fputc
fgets           读取一字符串
fputs
fread           读块
fwrite
fseek
rewind          文件流读写位置重设为开头
ftell           取得文件流读写位置
```

## 目录操作
```
opendir
readdir
closedir
mkdir
```

## 链接文件操作
```
symlink         建立软链接
link            建立硬链接
```

# X. 进程控制
## 进程的启动
* 手工启动是直接输入命令的启动方式。分为前台启动和后台启动。在输入的命令后追加&字符就是后台启动方式。
* 调度启动，使用at命令
常用的进程相关命令
```
ps      查看系统中的进程
top     动态显示系统中的进程
nice    按用户指定的优先级运行
renice  改变运行的优先级
kill    终止进程
crontab 用于安装,删除或者列出用于驱动cron后台进程的任务
bg      将挂起的进程放到后台执行
fg      后台进程转到前台执行
```
## 进程相关函数
```
getpid
getppid     父进程id
execXXX     包括execl, execlp, execv, execvp
system      
fork        创建新进程，新进程由复制当前进程得到
sleep
exit
_exit
wait        暂停父进程，等待子进程运行完成
waitpid     暂停父进程，等待子进程运行完成
```

## 进程的创建
```
pid_t fork(void);
    The fork() function shall create a new process. The new process (child process) shall be an exact copy.
    Upon successful completion, fork() shall return 0 to the child process and shall return the process ID of the child process to the parent process. Both processes shall continue to execute from the fork() function. Otherwise, −1 shall be returned to the parent process, no child process shall be created, and errno shall be set to indicate the error.

sample:
#include<stdio.h> 
#include<unistd.h> 
int main() 
{ 
    pid_t pid; 
    int count = 0; 
    pid = fork(); //fork一个进程 
    if(pid == 0)  //执行子进程 
    {
        printf("this is child process, pid is %d\n",getpid());
        count+=2; 
        rintf("count = %d\n",count); 
    } 
    else if(pid > 0) //执行父进程
    { 
        printf("this is father process, pid is %d\n",getpid()); 
        count++; 
        printf("count = %d\n",count); 
    } 
    else    //创建失败
    {
        fprintf(stderr,"ERROR:fork() failed!\n"); 
    } 
    return 0; 
}
```

```
execXXX包括execl, execv, execle, execve, execlp, execvp
    l   参数用列表传递方式
    v   参数用字符指针数组传递方式
    e   可指定环境变量
    p   路径自动搜索


int execl(const char *path, const char *arg, ... /* (char  *) NULL */);
int execlp(const char *file, const char *arg, ... /* (char  *) NULL */);
int execle(const char *path, const char *arg, ... /*, (char *) NULL, char * const envp[] */);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execvpe(const char *file, char *const argv[], char *const envp[]);

```

## 进程的终止
* 正常终止方式
    * main函数的return，等效于调用exit
    * 调用exit.   在调用_exit之前进行一些必要的收尾工作，包括文件缓冲区的写回。
    * 调用_exit.  _exit直接使进程停止运行，清除其使用的内存和在内核中的各种数据结构。
* 异常终止
    * 调用abort
    * 由一个信号终止

父进程已结束的子进程称作zombie僵尸进程。
wait函数用于父进程的阻塞，直到一个子进程终止或该进程接到了一个指定信号为止。

```
pid_t wait(int *stat_loc);
pid_t waitpid(pid_t pid, int *stat_loc, int options);
    wait for a child process to stop or terminate.
    The wait() and waitpid() functions shall obtain status information pertaining to one of the caller's child processes. Various options permit status information to be obtained for child processes that have terminated or stopped.
    The wait() function shall suspend execution of the calling thread until status information for one of the terminated child processes of the calling process is available, or until delivery of a signal whose action is either to execute a signal-catching function or to terminate the process. 
    this information may be interpreted using the following macros, which are defined in <sys/wait.h> and evaluate to integral  expressions; the stat_val argument is the integer value pointed to by stat_loc.    

       WIFEXITED(stat_val)
             Evaluates to a non-zero value if status was returned for a
             child process that terminated normally.

       WEXITSTATUS(stat_val)
             If the value of WIFEXITED(stat_val) is non-zero, this macro
             evaluates to the low-order 8 bits of the status argument that
             the child process passed to _exit() or exit(), or the value the
             child process returned from main().

       WIFSIGNALED(stat_val)
             Evaluates to a non-zero value if status was returned for a
             child process that terminated due to the receipt of a signal
             that was not caught (see <signal.h>).

       WTERMSIG(stat_val)
             If the value of WIFSIGNALED(stat_val) is non-zero, this macro
             evaluates to the number of the signal that caused the
             termination of the child process.

       WIFSTOPPED(stat_val)
             Evaluates to a non-zero value if status was returned for a
             child process that is currently stopped.

       WSTOPSIG(stat_val)
             If the value of WIFSTOPPED(stat_val) is non-zero, this macro
             evaluates to the number of the signal that caused the child
             process to stop.

       WIFCONTINUED(stat_val)
             Evaluates to a non-zero value if status was returned for a
             child process that has continued from a job control stop.   

```

## 守护进程daemon

守护进程的启动方式
* 启动脚本/etc/rc.d中
* 由作业控制进程cron启动
* 手动命令启动

守护进程变成要点
* 创建子进程，终止父进程。子进程以zombie形式存在。
* 为紫禁城创建新会话，使用setsid()。彻底从原父进程环境中独立出来。
* 改变工作目录，使用chdir()。
* 重设文件创建掩码，使用umask()
* 关闭从父进程继承的文件描述符。
```
关闭文件描述符
    for (i = 0; i< NOFILE; i++>)
        close(i);
```

```
pid_t setsid(void);
     create session and set process group ID
```

daemon进程脱离了终端，调试较为特殊，一般使用syslog()函数想/var/log/messages系统日志中写log的方法进行调试。使用命令tail观察
```
    tail -N /var/log/messages
```
# X. 进程通信
# X. 线程
# X. 网络变编程
## XX. TCP/IP
## XX. socket变成
# X. 图形编程
# X. 设备驱动程序设计
# X. 附录
## XX. 参考
* 金国庆，Linux程序设计，3rd，浙江大学出版社.
* [linux man manual](http://man7.org/linux/man-pages/man1/bash.1.html)
* [Advanced Bash-Scripting Guide](http://www.tldp.org/LDP/abs/html/)







