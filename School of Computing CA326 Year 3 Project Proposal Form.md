# School of Computing CA326 Year 3 Project Proposal Form

### Section A:

- __Project Title:__ ezsh (EasyShell)
- __Student 1 Name:__ James McDermott (__ID:__ 15398841)
- __Student 2 Name:__ Connor Mulready (__ID:__ 16302381)
- __Staff Member Consulted:__ Stephen Blott

#### Project Description:

ezsh (pronounced EasyShell) is to be user-friendly, and interactive shell designed to concretise a beginner's view of the terminal and usage of the command line. This will be written in C, using the popular library ncurses to build and interface. We hope to help solve the problem of beginner introduction to the shell with this project, creating a much more simple, and familiar surrounding than that other shells.

The inspiration for this project comes from extracurricular activities both of us have taken on outside of our academic studies. Over the years, both of us have been involved in tutoring secondary school students of all ages, from 12 right up to 18 when they come to university. This happened through our involvement in both CoderDojo in our local areas & ComputeTY. Pretty much anything you lay down for them, be it Python or Java for example, they would pick it up and run with it.

During this time, however, we found one consistent problem, namely the problem of introducing beginners to the command line on a Linux machine. First off, being a capable Linux user is just as important as being proficient in any language, if not more important in some aspects. In this regard, it makes complete and total sense that at some point they would be introduced to a shell environment such as BASH for example. This environment proved to be a stretch too far in some cases. Visualisation is a huge part of learning, and we feel this is what can impede on one’s first experience of the command line. Everything feels far away from the prompt, abstracted from view and existing somewhere you cannot see nor fathom.

We aim to develop a shell environment split into both an interface to the filesystem and a prompt. This is done in order to maintain a balance of regular command line usage at the prompt and increase the interactive nature of the shell environment. Along with this, we are adopting some concepts and functionalities found in your modern day browser such as Firefox or Chrome. We feel that this is the interface with which most people are familiar with on a computer. The aim of adopting such concepts ("favourites/bookmarks" for example) is to make the command line a more familiar setting for a beginner, and nothing more than a browser for your own personal computer and it’s filesystem.

---

#### Programming Language(s):
- We have agreed on moving forward with C as the primary language for the project, using the ncurses library for the interface to the filesystem. At the same time however, we have also looked at Golang as it boasts a strong range of terminal user interfaces libraries not all that different from ncurses.
- Our decision came down to which had the more extensive documentation, which was ncurses.

#### Programming Tool(s):
- We are using gcc as the compiler for this project. 
- In terms of libraries, as previously stated, we intend to make use of the ncurses to create an interactive environment for the shell.


#### Learning Challenges:
- The primary learning challenges we plan on facing during the development of our project would be firstly usability, creating a easy to use and learn interface and UI that would replace the steep learning curve that newcomers face when beginning to learn Linux with a more gradual slope.
- Secondly we'd be facing the challenge of learning a new language that would be suitable for the task at hand, this would inherently be C programming language due to its low level nature and prior relationship with Linux terminal.
- If we plan to create an extremely user friendly shell we will also need to have a comprehensive understanding of the role of the shell and various data structures. For example, our "favourites/bookmarks" and history commands will be implemented using two stacks. Understanding data structures in particular will be important as they will be fundamental to creating our own shell and making it a viable alternative to other shells. 
- Lastly there will be the challenge of learning new libraries that will help us greatly, more specifically ncurses library as it will allow us to add a user friendly interface that the user can easily interact with the shell whilst at the same time add a layer of abstraction to assist the user in understanding exactly what the shell is doing behind the scenes.


#### Hardware/Software Platform:
- ezsh will be designed to run on any distribution of Linux. 
- The platform which we will be testing and building the shell on is Ubuntu Linux.

#### Special Hardware/Software Requirements:
- N/A.

