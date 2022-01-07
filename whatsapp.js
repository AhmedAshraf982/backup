const { Client } = require('whatsapp-web.js');

const client = new Client();

client.on('qr', (qr) => {
    // Generate and scan this code with your phone
    console.log('QR RECEIVED', qr);
});

client.on('ready', () => {
    console.log('Client is ready!');
    // const number = "+923350319974";
    const number = "+923302809707";

  // Your message.

  // Getting chatId from the number.
  // we have to delete "+" from the beginning and add "@c.us" at the end of the number.
 const chatId = number.substring(1) + "@c.us";

 // Sending message.
 const msgs = ['hi','hello',':)','How are you?', 'sdf', 'sad', 'fgfgf', 'asa', 'adas', 'fgfg', 'sad', 'afas', 'dsfdf', 'dsfdsf', 'sdfdsg', 'ghgfh', 'asas', 'dsfdf', 'sadasd', 'gfdf', 'qwe', 'tuytu', 'ewewe'];
 const ahmed = "+923350319974@c.us";
 for(var x = 0; x < 100; x++){
    // var text = msgs[Math.floor(Math.random() * msgs.length-1)]
    var text = "Csgo?";
    client.sendMessage(ahmed, text);
 }
});
const sab_api = "923048609032@c.us"
const rec = "923302809707@c.us"
const ahmed = "923350319974@c.us";
const number = "923302809707@c.us";
const msgs = ['hi','hello',':)','How are you?', 'sdf', 'sad', 'fgfgf', 'asa', 'adas', 'fgfg', 'sad', 'afas', 'dsfdf', 'dsfdsf', 'sdfdsg', 'ghgfh', 'asas', 'dsfdf', 'sadasd', 'gfdf', 'qwe', 'tuytu', 'ewewe'];
client.on('message', msg => {
    if(msg.from == ahmed){
        // msg.reply(msgs[Math.floor(Math.random() * 4)]);
        msg.reply("Ok");
    }
});

client.initialize();