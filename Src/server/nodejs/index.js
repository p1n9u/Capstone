const express = require('express');
//const dbconfig=require('./config/database.js')
//const mysql=require('mysql');
const mysql= require('mysql');
//const hostname = '166.104.185.49';
//const connection = mysql.createConnection(dbconfig);
const connection=mysql.createConnection({
	host:'localhost',
	user:'root',
	password:'asdf1234.',
	database:'ecgdb',
	connectionLimit :5 
});


const app=express();

connection.connect(function(err){
	if(!err){console.log("db is connn");}
	else {console.log("error connecting db");}
});

app.set('port',process.env.PORT || 8087);

/*
app.get('/', (req,res)=>{
	res.send('ROOT');
});
*/

app.get('/', (req,res)=>{
	console.log('app.get!');
	connection.query(`select * from ecgtb`, (error,rows,fields)=>{
		console.log('ififififif');
		if(error) {console.log( error);}
		console.log('user info is : ', rows);
		res.send(rows);
	});
	console.log('endendendend');
});


app.listen(app.get('port'),()=>{
	console.log('express server listening on port ' + app.get ('port'));
});




