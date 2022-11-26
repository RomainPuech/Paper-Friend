# TextEditor Based on QT document

## 1. Introduction

This is a simple TextEditor inner the PaperFriend Appliation which allow our client to process the text file with some basic function. The TextEditor is available for both Windows and MacOS.

## 2. Configuring the environment

> QT creator
>
> Visual Studio

---

## 3. Structure of the Source Code

We use **QT Creator** to create the TextEditor application based on the framework of **Qt Widgets Application** with beautifully designed and easy to use GUI and easy programming of functions in Widgets.

The framework of the TextEditor is shown as below:
- Editor.pro
- **Headers**
  - edit.h
  - textedit.h
- **Sources**
  - main.cpp
  - edit.cpp
  - textedit.cpp
- **Forms**
  - textedit.ui
- **Resources**
  - myresources.qrc

The cpp source file which is most base on `textedit.cpp` and `edit.cpp` which accomplish the basic function of the TextEditor. The `textedit.ui` is the UI file which is used to design the GUI of the TextEditor. The `myresources.qrc` is the resource file which is used to store the icon of the TextEditor. The `edit.h` and `textedit.h` are the header file which is used to declare the class of the TextEditor.

---

## Testing Report

1. When saving files, the no button still asks you to save the file.
2. When the file is saved, the warning box still jump out.
