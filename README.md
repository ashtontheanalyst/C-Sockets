# Socket Programming in C on Windows
<img src="./diagrams/State%20for%20Server%20Client%20Model.jpeg" alt="Alt Text" height="400">


**Following:** 'Beej's Guide to Network Programming' https://beej.us/guide/bgnet/html/split/index.html
<br><br> 


### WSL - Windows Subsystem for Linux
This application allows us to run a real LINUX environment inside Windows without a virtual machine
or a second boot. Since Beej's guide is mostly around Linux environments, it would be better to have a
computer that acts and behaves as such.
```sh
# Instal WSL in powershell terminal, VSCode WSL and C/C++ extensions
wsl --install
code --install-extension ms-vscode-remote.remote-wsl
code --install-extension ms-vscode.cpptools
```


#### Opening a Folder with WSL
Now that both the local and VSCode extension of WSL have been installed. Open VSCode as
normal on the Windows laptop, go to the folder containing your code, in the lower left
hand corner of VSCode there will be a little blue box with '><' in it, click it. Select
'Connect to WSL', then open your Git repository using your Github account. You should now
have a Linux terminal when you click 'Ctrl + `'
```sh
# Get the WSL system up to date, git ready, and gcc compiler installed
sudo apt update
git config user.email "email@some.com"
git config user.name "user"
sudo apt install gcc
```


### C Reminders
```sh
# Compiling code
gcc fileName.c -o outputName
# Running the output
./outputName
```