const express = require('express');
const nedb = require('nedb');
const data = new nedb('database.db');
const msgs = new nedb('messages.db');
const bodyParser = require('body-parser');
const path = require('path');
const axios = require('axios');
const { NONAME } = require('dns');
const { response } = require('express');
const PORT = process.env.PORT || 5000;
const params = {
    access_key: '0e2c2c4267ab9852ed4d1edd800e802'
  }
const app = express();
data.loadDatabase();
msgs.loadDatabase();
app.listen(8000, () => {
    console.log("Listening to port 8000");
});
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.get('/', (req, res) => {
    res.sendFile(__dirname + '/index.html');
});
app.get('/index.html', (req, res) => {
    res.sendFile(__dirname + '/index.html');
});
app.get('/register.html', (req, res) => {
    res.sendFile(__dirname + '/register.html');
});
app.get('/app.html', (req, res) => {
    res.sendFile(__dirname + '/app.html');
});
var user;
app.post('/send', (req, res) => {
    console.log("Request from: ", req.body.id);
    data.findOne({ id: req.body.id }, function(err, doc) {
        if(doc == null){
            console.log("User not found!");
            res.redirect('/register.html');
        }else{
            fname = doc.fname;
            user = fname;
            lname = doc.lname;
            id = doc.id;
            pass = doc.pass;
            console.log('Found user:', doc.fname);
            var url = '/app.html?id=' + id + '&fname=' + fname + '&lname=' + lname + '&pass=' + pass;
            res.redirect(url);
        }
    });
});
app.get('/user.html', (req, res) => {
    res.sendFile(__dirname + '/user.html');
});
app.get('/getUsers', (req, res) => {
    data.find({}, function(err, doc){
        if(err){
            console.log('error');
            throw err;
        }else{
            res.json(doc);
        }
    });
});
app.get('/getMsgs', (req, res) => {
    msgs.find({}, function(err, doc){
        if(err){
            console.log('error');
            throw err;
        }else{
            res.json(doc);
        }
    });
});
app.post('/message', async (req, res) => {
    const dateString = new Date().toLocaleString();
    var options = {
        sender: req.body.sender,
        receiver: req.body.receiver,
        date: dateString,
        msg: req.body.msg
    }
    console.log(options);
    msgs.insert(options, function(err, doc){
    });
});
app.post('/regUser', async (req, res) => {
    var options = {
        fname: req.body.fname,
        lname: req.body.lname,
        id: req.body.id, 
        pass: req.body.pass
    }
    data.insert(options, function(err, doc){
        if(!err){
            console.log("Inserted user: ", doc.fname);
        }
    });
    res.redirect('/index.html');
});