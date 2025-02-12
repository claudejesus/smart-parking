wokwi link: https://wokwi.com/projects/422527130779917313

apppscript code:
https://script.google.com/u/0/home/projects/1WpSayIphR9RGmmY75MWLi5aqHnMhfHnFkq38r0H-bLeOto47qQ7FX0Mt/edit

google link: 
https://docs.google.com/spreadsheets/d/1XjC9yOebiRO1oPzjDGOCmLDsr2oHZSFguUrPgbjTlEk/edit?gid=0#gid=0

how project work
-----------------------------------------------------------------
Objective:  
As a B.Tech student in IT, you are tasked to collaborate with ABC Company to design a smart car parking 
system. Your role is to simulate the parking system's functionality using Wokwi and VS Code. The system 
will utilize Google Sheets as cloud storage to manage parking space data, enabling users to monitor available 
spaces remotely.  
Assignment Details: 
The car parking system will have the following features: 
1. User Interaction via Buttons and Sensors: 
o Button 1 (Entry Confirmation): 
▪ When pressed, the system simulates a vehicle entering the parking area. 
▪ Actions: 
▪ The motor opens the parking gate (indicated by o LED1 simulating the gate). 
▪ The total available parking spaces are reduced by one. 
▪ The gate remains open for 3 seconds before automatically closing. 
• Button 2 (Exit Confirmation): 
o When pressed, the system simulates a vehicle exiting the parking area. 
o Actions: 
▪ The motor opens the gate for vehicle exit. 
▪ The total available parking spaces are increased by one. 
▪ The gate closes automatically after 3 seconds. 
• Button 3 (Manual Update): 
o Allows the operator to manually adjust the total number of parking spaces in case of system 
errors or maintenance. 
Real-Time Monitoring: 
• The number of available parking spaces will be displayed: 
1 
o Locally on an LCD connected to the system. 
o Remotely on an HTML page hosted on GitHub Pages. 
• The HTML page will allow users to: 
o View the real-time count of free parking spaces. 
o Ensure users can monitor, but not modify, the parking space count directly from the page. 
2. Cloud Integration with Google Sheets: 
• The system will send and retrieve data from Google Sheets, which acts as the backend for managing 
parking space availability. 
3.  Scalability Demonstration: 
• Run the system on three different computers simultaneously to demonstrate that multiple users can 
access real-time parking availability data without conflicts.  
Implementation Tools: 
1. Wokwi: For simulating the embedded system hardware (e.g., buttons, motor, sensors). 
2. VS Code: For coding and debugging the embedded system. 
3. Google Sheets API: For integrating cloud storage to manage parking space data. 
4. HTML/JavaScript: For creating a GitHub-hosted monitoring page.  
Tasks: 
1. Simulate the car parking system using Wokwi: 
o Implement button functionalities for entry, exit, and manual updates. 
o Use a servo motor or LED to simulate the gate opening and closing. 
2. Integrate Google Sheets for real-time data synchronization. 
3. Develop an HTML page to display the real-time count of available parking spaces. 
4. Demonstrate scalability by running the system on three different computers simultaneously. 
Evaluation Criteria: 
1. Correct functionality of the simulation (e.g., button operations, motor behavior). 
2. Accurate integration with Google Sheets for parking space management. 
3. Usability and design of the HTML monitoring page. 
4. Successful scalability demonstration across three computers. 
