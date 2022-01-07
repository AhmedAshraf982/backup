// // token: ODYxMjY0NDU2Nzc5Njk0MDgw.YOHRCA.3plk2dtIsuyKMyRHlf0IKg_yC1g

// var Discord = require('discord.io');
// var logger = require('winston');
// var auth = require('./auth.json');
// const minigames = require('discord-minigames');
// const { MessageMedia } = require('whatsapp-web.js');
// // Configure logger settings
// logger.remove(logger.transports.Console);
// logger.add(new logger.transports.Console, {
//     colorize: true
// });
// logger.level = 'debug';
// // Initialize Discord Bot
// var bot = new Discord.Client({
//    token: auth.token,
//    autorun: true
// });
// bot.on('ready', function (evt) {
//     logger.info('Connected');
//     logger.info('Logged in as: ');
//     logger.info(bot.username + ' - (' + bot.id + ')');
//     console.log("Bot is listening...");
// });
// bot.on('message', function (user, userID, channelID, message, evt) {
// // bot.on('message', message => {
//     // let member = message.mentions.members.first()
//     // Our bot needs to know if it will execute a command
//     // It will listen for messages that will start with `!`
//     if (message.substring(0, 1) == '!') {
//         console.log(message);
//         var args = message.substring(1).split(' ');
//         var cmd = args[0];
       
//         args = args.splice(1);
//         switch(cmd) {
//             // !ping
//             case 'ping':
//                 bot.sendMessage({
//                     to: channelID,
//                     message: 'Pong!'
//                 });
//             break;
//             // Just add any case commands if you want to..
//             case 'battle':
//                 minigames.startBattle('member', message)
//             break;
//          }
//      }
// });

/* DEFINE DISCORD AND DISCORD-MINIGAMES */
const Discord = require('discord.js')
const minigames = require('discord-minigames')
/* CREATE DISCORD CLIENT */
const client = new Discord.Client()

getGame = function(){
    str = '';
    for(var x = 0; x < 10; x++){
        for(var y = 0; y < 10; y++){
            str += '☐';
        }
        str += '\n';
    }
    return str;
}
/* ON READY EVENT */
client.on('ready', () => {
    console.log(`${client.user.username} is online!`)
})

let prefix = "!" /* You can change this to your desired prefix. */

/* MESSAGE EVENT */
client.on('message', message => {
    let member = message.member
        /* BATTLES */
        if (message.content == '!ping'){
            message.channel.send('!pong')
        }
        else if (message.content == '!snake') {
            snake = getGame();
            message.channel.send(snake);
        /* ISPYS */    
        }
        else if(message.content == '!kratos'){
            message.channel.send("God of War", {files: ["https://bloody-disgusting.com/wp-content/uploads/2020/12/godofwar.jpg"]});
        }
})
client.login('ODYxMjY0NDU2Nzc5Njk0MDgw.YOHRCA.3plk2dtIsuyKMyRHlf0IKg_yC1g')