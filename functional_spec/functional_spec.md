# Functional Specification For ezsh

__Student 1:__ James McDermott
__Student Number:__ 15398841

---
__Student 2:__ Connor Mulready
__Student Number:__ 16302381

---
__Supervisor:__ Dr. Stephen Blott
__Completion Date:__ 07/12/2018

---

## 0 Table of Contents

0. [__Table of Contents__](#0-Table-of-Contents)
1. [__Introduction__](#1-Introduction)
    - 1.1 Purpose
    - 1.2 Scope
    - 1.3 Document Conventions
    - 1.4 Document Outline
2. [__Description__](#2-Description)
    - 2.1 Product Perspective
        - 2.1.1 Product Interfaces
        - 2.1.2 Interfaces
    - 2.2 Product/System Functions
    - 2.3 User Characteristics and Objectives
    - 2.4 Operating Environment
    - 2.5 Constraints
3. [__Functional Requirements__](#3-Functional-Requirements)
    - 3.1 Perform as a Shell (Prompt)
        - 3.1.1 Description
        - 3.1.2 Criticality
        - 3.1.3 Technical Issues
        - 3.1.4 Dependencies with other requirements
    - 3.2 File System (Explorer)
        - 3.2.1 Description
        - 3.2.2 Criticality
        - 3.2.3 Technical Issues
        - 3.2.4 Dependencies with other requirements
    - 3.3 Dynamic Infographic
        - 3.3.1 Description
        - 3.3.2 Criticality
        - 3.3.3 Technical Issues
        - 3.3.4 Dependencies with other requirements
    - 3.4 The Server
        - 3.4.1 Description
        - 3.4.2 Criticality
        - 3.4.3 Technical Issues
        - 3.4.4 Dependencies with other requirements 
4. [__System Architecture__](#4-System-Architecture)
    - 4.1 Diagram - System Architecture
    - 4.2 Diagram Description
5. [__High Level Design__](#5-High-Level-Design)
    - 5.1  Diagram - DFD
        - 5.1.1 Diagram Description
    - 5.2  Diagram - LDS
        - 5.2.1 Diagram Description
6. [__Preliminary Schedule__](#6-Preliminary-Schedule)
7. [__Appendices__](#7-Appendices)
    - 7.1 Appendix A (Intercommunication of Panes)
    - 7.2 Appendix B (References)

---

## 1. Introduction

#### 1.1 Purpose
The purpose of this functional specification is to define what ezsh (pronounced *easy shell*) is, and what problems it hopes to resolve as a system. Upon reading this document to completion, the reader should firmly understand the key objectives, design and technical aspects of ezsh at a high level.

#### 1.2 Scope
ezsh is a introductory, user-friendly, and interactive shell for new and inexperienced users to the general Linux environment. The primary objective of ezsh is to help reduce the steep learning curve that is present in the most shells (for example, Bash), all the while allowing the users to interact with a new environment.

It aims to do this by introducing a fully functional, and familiar feeling GUI. This GUI will be achieved by making use of the ncurses library and tmux. The specific of how these are to be used in conjunction with ezsh will be discussed in further section of this document. As a comment, the group hopes to boost the user-friendliness and interactiveness of ezsh using both ncurses and tmux.

To achieve all of this, the different components which make up ezsh must interact with a server. As a consequence of our current development and testing environments, ezsh is being developed to only run on Linux distributions.

#### 1.3 Document Conventions
Whenever the reader sees the phrase _'the shell'_, it will be referencing ezsh.
The term _'explorer'_ direclty corrolates to ncurses (Appendix B) file system explorer pane.
The phrase _'infographic'_ similar to _'explorer'_ is a ncurses pane primarily used for displaying useful information to the user.

#### 1.4 Document Outline
This functional specification contains a further four sections following this section.
__Section 2__ aims to cover the overall purpose of the shell, it's objectives, features, constraints and environment. This section gives a high level overview.
__Section 3__ plans to delve deeper than __Section 2__, looking at technical requirements, potential technical issues, and the shell's dependencies. This section gives a lower level overview.
__Section 4__ aims to give a clearer perspective to the reader about how aspects discussed in __Section 3__ will be achieved by the group. This section servers to provide the user with  a clearer understanding of the shell's overall architecture.
__Section 5__ combines __Section 2__ to __Section 4__ inclusive and will provide a high level description of the shell accompanied by diagrams to explain the data flow around the shell and logical structure of the shell.

---

## 2. Description

#### 2.1 Product Perspective
The objective of the shell is to make the transition to the shell environment easier to new an inexperienced users. The leap from the everyday use fo a computer to these new surroundings is often confusing and even leap too far for some. Aiming to help aid this issue, the group also hope to passively help the user grow accustomed to the shell and slowly help abolish the daunting and steep learning curve often posed to new users of the shell on a Linux system.

#### 2.1.1 Product Interfaces
As stated above in Section 2.1, the shell's key aim is to remove the steep learning curve that other shells have. In order to achieve this objective set by the group, they plan on introducing the user to a graphical user interface that shares similar qualities with ones they were most accustomed to up to this point. 

The group took time to deliberate what this would be, and finally deemed that the interface that newcomers would be most familiar with, up to this point anyways, would be the browser. Almost everyone, from young to old, has had at least some interaction with a browser, arguably this is the most used software on any of their devices. Acknowledging this, the group hopes to bring more familiarity to the shell environment through introduction of concepts found in the browser. Concepts include favourites/bookmarks, back/forward, and a home icon. With all this, we hope to reduce the daunting interface that comes built into the default Bash shell.

The group primarily aims to introduce these features in the explorer pane (left hand side), which is to act as the "My Computer" or "Finder" in the shell. The introduction of this pane, in the groups opinion, will boost interactivity and concretise a beginner's view of the shell in relation to the rest of the computer.

Whilst increasing usability through this GUI with the explorer pane, the group also has the objective of not isolating the user solely to the shell, their aim is to create an introductory environment so that at a later time the user can inherently return to Linuxs default shell. Therefore it was essential that the group not completely replace the prompt (bottom right handside) in favour of a interactive GUI but instead simplify it. 

Finally to concretise any abstract ideas the group opted to use a infographic pane (top right handside). This pane would not receive input from the user but would act as a helping hand by displaying commonly used commands and demonstrating the data structures that are used to operate the shell. The objective with this is to reduce the amount of isolation a user is abruptly placed into with other shell environments and introduce them while passively showing how data structures work.

#### 2.1.2 Interfaces
__ezsh Help Infographic UI MockUp__

![](https://i.imgur.com/wxvmDqw.png)

*- Infographic displaying common commands, prompt displaying executed command 'HELP git pull' and demonstrating autocompletion, and the explorer pane on the left-hand side.*

---

__ezsh Data Structure Infographic UI MockUp__

![](https://i.imgur.com/TxAazzY.png)

*- Infographic displaying the file system dynamically as a tree*

---

#### 2.2 Product/System Functions
- Prompt
    A huge component of any shell is its prompt. *This almost goes without saying in most cases, but in this shell the prompt only one component.* The prompt will offer users the ability to operate within their own terminal as usual. The prompt itself comes with some built-in commands. 
    - Examples of built-in commands:
    
        - help:
        The help command will simplify man page output, clearly explaining what a commands intended use is.
        - star:
        The star command will add a directory or file to a log of other directories/files the user had "starred". This is intended to represent the bookmark's functionality found within a browser. The user will be able to call from these starred directories/files using the star command followed by the alias of the directory/file starred by the user.
    - Autocompletion:
    The prompt will also come with an auto completion feature. When the user enters a command, the prompt will make suggestions based on the contents of the current directory along with what they has entered so far.

- Explorer
    The explorer pane will accentuate the interactiveness and user-friendliness of the shell. This pane acts as the "My Computer" or "Finder" of the shell. The explorer comes built in with these capabilities:
    - Changing Directories:
    The explorer allows the user to change between directories by mouse click or navigating to a desired directory followed by the return key. This acts as a bridge between the usual layout users expect when viewing the file system on a computer, and this newer environment. This aids the user while providing them with them know how to operate around the filesystem.
    - Opening Files:
    The explorer allows the user to open files for editing with a default editor of the user's choice. This choice of default editor will be selected the first time a user opens a file.
    - Shortcuts:
        - Stars:
        The star command will also be available to the explorer pane as well as the prompt. This can be seen in the diagram in section 2.1.2 where it acts as a shortcut to invoking the star command in the prompt itself.
        - Back/Forward
        This acts as a shortcut between the previous directory (the same as `cd ..`) and hitting return on the current selected directory respectively.
        - Home
        This shortcut icon simply returns the user to their home directory (the same as `cd`).
- Infographic
    The user doesn't interact with this pane except for toggling it between the filesystem display and the useful commands pane.
    The filesystem display shows where the user currently resides in the filesystem.
    The useful commands shows the user commonly used commands. If a user grows accustomed and comfortable with certain commands, the system will swap said command out for a new one that the user has not used often.


#### 2.3 User Characteristics and Objectives
The shells expected user base will primarily consist of inexperienced Linux users, this could be a beginner programmer whether it be a student or someone doing it as a hobby. A Linux user who is not comfortable with the default shell or finds it tedious.
The group plans to make the shell publicly available online to anyone who wishes to use it.

#### 2.4 Operating Environment
The shell will operate strictly only in Linux environments. This means it will be able to operate on multiple Linux distributions. These distributions include Ubuntu, Fedora, OpenSUSE and many others.

This decided for two main reasons:
1. Most (if not all) of the development and testing of the shell will take place on either Ubuntu(our own machines) or OpenSUSE(DCU machines)
2. We are significantly more familiar with the Linux family of operating systems than any other.



#### 2.5 Constraints
Below you will find a set of constraints and limitations placed upon the group who are developing the shell

- Time Constraints
    Time is of the essence in the development of the shell. The third year project itself must be completed and submitted by March 8th 2019, with a presentation taking place shortly after this.
    
    In between now and then, each member of the group has 6 exams they study for over the Christmas break.
    
    Due to all of this, it is imperative the group closely follows the Preliminary Schedule which they set out.
    
- Operating Environment
    As outlined in section 2.4, the shell is strictly for Linux environments only. While the members of the group find themselves more experienced with this set of operating systems in particular, this nonetheless limits the group to developing and testing the shell.

- Scale of Project
    The group behind the shell have not used the C programming language on this scale before. 
    
    Objectively the group acknowledges that further research and upskilling must be taken in the next three weeks to one month in order to ensure the development process on a project of this scale is as smooth as possible.

- Multiplexer
    As stated later in section 4.2, the shell will be using a multiplexer to manage separate programs in separate panes within the same window.
    
    At this time, the group has chosen `tmux` as the multiplexer which will aid the shell in this way. However, if development is ahead of schedule at a later date, we would like to implement these panes without the aid of tmux to create them

---

## 3. Functional Requirements 

### 3.1 Perform as a Shell (Prompt)

#### 3.1.1 Description
As the shell aims to replace Linux's default shell, the group doesn't aim to recreate the wheel, but rather simplify it. Therefore, it is imperative that it be able to carry the same functionality that other shells can, but with the addition of a helping hand in the explorer pane and the infographic pane.

#### 3.1.2 Criticality
The aspect of the groups prompt performing the core commands and features of the default shell is key to our product. By enabling this we can ensure that the user won't be deprived of any valuable information at the fault of ezsh. The only time this should occur is when the user reverts or turns to the default linux shell and attempts to use a ezsh exclusive command such as 'HELP'.

#### 3.1.3 Technical issues
As the shell consists of many panes one of which is used for conveying information and the other for directly interacting with the other components, one main issue that could arise is that of intercommunication (Appendix B) of processes from separate panes.

#### 3.1.4 Dependencies with other requirements
As stated previously in section 3.1.3 the prompt must be able to interact with other panes through processes and requests therefore if the user executes a command that uses a relevant data structure the prompt must be able to convey this to the infographic pane and if the user changes directory through the file explorer the prompt must receive that request and update accordingly.

### 3.2 File System (Explorer)

#### 3.2.1 Description
The file explorers primary function is to allow the user to easily navigate through their file system in real time whilst displaying the commands being executed to perform such actions. It also aims to increase productivity by providing such features as 'back' (arrow left), 'forward' (arrow right), 'add favourite' (star to left of directory), 'view favourites' (star at top and right of home) and 'home' (double arrow left <<).

#### 3.2.2 Criticality
It is critical to achieve a user friendly graphical user interface that is NOT cluttered and that should be familiar to any user who comes across it. 

#### 3.2.3 Technical issues
Key issue is to find a optimum user interface that is easy to interact with and to have user data persist over multiple sessions

#### 3.2.4 Dependencies and other requirements
The file system explorer must be able to observe the creation or deletion of any new directories from outside the explorer and update accordingly. Failure to do so will lead to inconsistencies therefore it must be able to communicate seamlessly with the prompt as explained in Appendix A.


### 3.3 Dynamic Infographic
#### 3.3.1 Description
The dynamic infographic pane will deliver the most popular commands available in Bash whilst displaying the shells own custom commands. 
It also will deliver a concretised view of data structures that would normally occur without the users knowledge in the background when certain commands are executed.

#### 3.3.2 Criticality
The dynamic infographic pane will not have an effect on the overall system as it simply aims to display and show the user how certain data structures are executed and interacted with and where they are used in a real world application therefore further solidifying the users knowledge and increasing their confidence.

#### 3.3.3 Technical issues
Allowing the user to manually alternate between command view and data structure view. Automatically alternate views depending on if a data structure event occured.
Being able to detect when a data structure event occurs as inter-pane communication must occur.
Visually representing a accurate real time model of the data structure and the event occuring to it.

#### 3.3.4 Dependencies and other requirements
The dynamic infographics heavily depends on the requirements previously mentioned in sections 3.1 and 3.2 as it must wait for either the prompt or the file system explorer to execute an appropriate command.

### 3.4 The Server
#### 3.3.1 Description
The server allows the intercommunication of the different components, allowing data to change one one pane in accordance with another pane. This means changes made though the prompt can be displayed on the explorer or infographic.

#### 3.3.2 Criticality
The server is of the utmost importance as this is what bridges the gap between each individual component of this shell. Without it, changes can not be made between different panes, changes are static in so far as they apply to one pane and one pane only. The server is vital to the shell as we envision it.

#### 3.3.3 Technical issues
Having the server up and running will require extensive Unix socket programming. Sockets are communication points on a computer which can be used to exchange data. In this case, changes made in panes will be relayed using sockets to other panes.

#### 3.3.4 Dependencies and other requirements
The server depends on the usage of sockets to relay information. Apart from that, the server won't rquire any further dependencies to run.

--- 

## 4. System Architecture

#### 4.1 Diagram
![](https://i.imgur.com/GNso9ro.png)

#### 4.2 Diagram Description
Our System Architecture Diagram shows the arrangement of the different components that make up the shell. 

The shell is made up of an `Explorer`, an `Infographic`and a `Prompt`. Each of these programs run in a separate `Pane` in the same `Window`. This window is split into the three panes, the `Explorer`, the `Prompt` and the`Infographic`. These components are said to make up the GUI of the shell.

This `Window` is found in a single `Session`, which itself is managed and launched by the `Multiplexer` (Appendix B). As stated in section 2.5, the multiplexer this group will be using is tmux (Appendix B), though implementation of the specific functionality the group require from tmux may be carried out at a later date if development is found to be significantly ahead of schedule.

This `Multiplexer` can be seen as a way to manage the three programs independently of each other. The transmission of data from one to the other is facilitated by the `ezsh server`. This waits for changes/actions to be taken in either the `Explorer` pane or the `Prompt` pane and transmits data to the other panes where appropriate. 


---

## 5. High Level Design

#### 5.1 Data Flow Diagram
![](https://i.imgur.com/94CjSxD.jpg)

#### 5.1.1 Description
The shell will allow the user to interact with two panes, the `prompt` and the `explorer`. 

The `prompt` will take user input and check if the data is syntactically correct. 
If so it will proceed to find and execute the correct command, else the user will receive and error. Once the the command is executed the Linux kernel will update accordingly and in turn the user interface will be updated based of the command entered.

The `explorer` can also be directly interacted with. When the user changes directory through the `explorer` the request will be passed to the kernel which will update the correct process.

Since both available inputs will have to be processed through the Kernel the UI will be updated for the entire Shell.

#### 5.2 Logical Data Structure
![](https://i.imgur.com/sd51ry9.jpg)
#### 5.2 1 Description
The logical data system aims to provide a high level overview of how the user will interact with the system. 

The user will issue a command to either the `prompt` pane or the `explorer` pane. Any and all input/commands passed to either pane will be passed through to the server using Unix sockets. This server will manage all panes in the tmux session, the Infographic, the Explorer, and the Prompt. 

The server receives data from one of two panes, the Explorer or the Prompt. From here it updates any of the other two panes when appropriate.

---

## 6. Preliminary Schedule
| Sprint   |    Length     |    Start    |    End    |  Objectives     |
|----------|:-------------:|------------:|----------:|----------------:|
|    1     |  Two weeks    |   7/12/18   | 21/12/18  | Upskilling in C |
|    2     |  3 days       |   21/12/18  | 23/12/18  | Tmux Integration|
|    3     |  5 days       |   04/01/19  | 08/01/19  | Basic Prompt|
|    4     |  Two weeks    |   08/01/19  | 22/01/19  | Server|
|    5     |  One week    |   22/01/19  | 29/01/19  | Explorer|
|    6     |  One week    |   22/01/19  | 29/01/19  | Explorer-Prompt Server Integration|
|    7     |  4 days    |   29/01/19  | 01/02/19  | Command Infographic|
|    8     |  One week    |   01/02/19  | 08/02/19  | Prompt Features|
|    9     |  Two weeks    |   01/02/19  | 08/02/19  | Data Structure Infographic|

---

## 7. Appendices
#### Appendix A
##### Intercommunication of Panes
Panes will be statically rendered however since they're separate processes, they will not be able to communicate directly by default. Therefore providing a universal message passing system is mandatory.

This will be done using unix sockets.
This was not included in Section 3 as it deals with the systems design rather than functionality.

#### Appendix B
#### References
- [ncurses](https://www.gnu.org/software/ncurses/) --> https://www.gnu.org/software/ncurses/
- [Unix Sockets](http://man7.org/linux/man-pages/man2/socket.2.html) --> http://man7.org/linux/man-pages/man2/socket.2.html
- [Multiplexer](http://linuxcommand.org/lc3_adv_termmux.php) --> http://linuxcommand.org/lc3_adv_termmux.php
- [tmux](http://man7.org/linux/man-pages/man1/tmux.1.html) --> http://man7.org/linux/man-pages/man1/tmux.1.html
