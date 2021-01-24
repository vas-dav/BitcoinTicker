# RealTime-Crypto-Ticker by Vasily Davydov

 #### INFO
- This device is making a connection with a `pro-api.coinmarketcap.com` using own API key. 
- Gathers the Data, converting it to the Json document
- Prints current Bitcoin & Ethereum price with 24% change on a physical LCD screen updating it every 5 minutes
- Switches every 9 seconds between Bitcoin and Ethereum Data
- [Mikhail Stefantsev](https://github.com/MStefan99) has contributed in a server-side code of this project

#### Some notes:
> The main program code is in **TEST** mode using `sandbox-api.coinmarketcap.com` **host** and `b54bcf4d-1bca-4e8e-9a24-22ff2c3d462c` **test API**
> This is due to limitation of `pro-api.coinmarketcap.com`, which allows only 333 connections per day with a personal API


#### Parts used in this project:
- [NodeMcu v1.0 with ESP8266](https://arduino-esp8266.readthedocs.io/en/latest/)
- [16x2 LCD screen](https://components101.com/16x2-lcd-pinout-datasheet)
- [220Ohm Resistor](https://www.amazon.com/EDGELEC-Resistor-Tolerance-Multiple-Resistance/dp/B07QK9ZBVZ/ref=sr_1_1_sspa?dchild=1&keywords=220+ohm+resistor&qid=1611518460&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExQVk1NlhZMzAzQURNJmVuY3J5cHRlZElkPUEwMDQyODQwTUtUR09EVzFJRzkwJmVuY3J5cHRlZEFkSWQ9QTAwMjk4MTgyWlBWU1lJVFdKUFEzJndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==)
- [Jumper Wires](https://www.amazon.com/EDGELEC-Breadboard-Optional-Assorted-Multicolored/dp/B07GD2BWPY/ref=sr_1_1_sspa?dchild=1&keywords=jumper+wires&qid=1611518487&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEzRFZNN0RZR1VHVjE5JmVuY3J5cHRlZElkPUEwMjU0NDA2WDhOREwwV0JBMEwxJmVuY3J5cHRlZEFkSWQ9QTA5NDU0MzYxSkE3VExKQkZEQUxaJndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==)

## Example of powering ON:
### Start-up screen 
![Power ON](FilesforREADME/pic1.png)
### Connecting to a WiFi router
![Connecting...](FilesforREADME/pic2.png)
### Connecting to a server
![Server](FilesforREADME/pic3.png)
### Updating gathered Data 
![DATA Updated](FilesforREADME/pic4.png)
### Showing the data of Bitcoin 
![Bitcoin](FilesforREADME/bit.png)
### Showing the data of Ethereum
![Ethereum](FilesforREADME/eth.png)


