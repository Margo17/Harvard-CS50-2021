# Chrome extension Work hard, play later

## Author: Martynas Goberis

### Video Demo: <https://youtu.be/_B80qnxCrYM>

#### Description:

**_Work hard, Play later_** is a simple procrastination blocker which helps you to stay focused on your work. If you are busy with conentration requiring tasks and try to waste time on youtube, facebook, discord etc. it blokcs these websites and reminds you to get back to work while also displaying some calming clouds in the background.

#### File list:

- manifest.json
- content.js
- popup.html
- portfolio64.png
- portfolio128.png
- README.md

#### File explanation:

##### manifest.json

Manifest.json is a required javascript object notation type parameter file for Google Chrome extensions. It specifies all the main details of the application like manifest version (specification format by Google), name, program version, content scripts, icons and actions in a browser. In other words - it is the main setup file.

##### content.js

Content.js is where all the magic happens. Two main functions do the work here. These functions are generateSTYLES and generateHTML. GenerateSTYLES simply inserts the required CSS for the clouds and fonts to display when an entered procrastination page is blocked. Similarly generateHTML inserts the hyper-text markup to add text division elements and required text to be modified. At the end of the script a switch statement is declared. It checks what page URL is activated and replaces inner HTML inside the head and the body of the index page. Finally, with this new HTML custom styles can be applied.

##### popup.html

Popup.html's purpose in life is to create content inside the extensions popup (activated by selecting Chrome extension menu in upper-right corner and clicking on the app icon). This is done by HTML. The content itself is a reminder 'Don't waste your time' and a list of currently blocked websites. Additional websites can be inserted by modifying the source code inside popup.html and content.js.

##### portfolio64 and portfolio128

These png images are for aesthetic purposes. The 64 bit version is shown in the popup window and the 128 one is displayed in the extension settings menu.

##### README.md

This file specifies all the details of the application. And you are currently reading it! :memo:

#### Conclusion

CS50 was an outstanding course and this project shows my overall understanding of computer science basics. I am thankful to Harvard's staff and wish them best of luck. **_This was CS50!_**
