const express=require("express"); //npm으로 설치한 라이브러리 불러옴

const app=express();

// var moment = require('moment');
 

app.use(express.urlencoded({extended: true}));
app.use(express.static('static'));

 

app.get("/",(request,response)=>{

//   response.send("Hello world");


});

 

app.post("/",(request,response)=>{

    response.send("Hello test");

 

});

 

 

 app.listen(8081, (e) => {

 

    console.log("hello world", e);

 });
