var Websockets= 38887;
var clientId ='client_Id_'+Math.floor((Math.random()*1000000)+1);
client = new Paho.MQTT.Client("driver.cloudmqtt.com",Websockets,clientId);
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;
var options ={
    useSSL:true,
    userName:"xuzybaen",
    password:"CTEGwRzS4Mza",
    onSuccess:onConnect,
    onFailure:doFail
}
client.connect(options);

function onConnect(){
    console.log("Exito en coneccion!!");
    $("#status").html("Conexion Establecida");
    client.subscribe("salidaCubo");
}

function onMessageArrived(message){
    console.log("Mensaje de llegada:"+ message.payloadString);
    $("#display").html(message.payloadString);
}

function doFail(e){
    console.log(e);
}

function onConnectionLost(responseObject){
    if(responseObject.errorCode!== 0){
        console.log("onConecctionLost:" + responseObject.errorMessage)
    }
}
function command(value){
    console.log(value);
    message=new Paho.MQTT.Message(value+"");
    message.destinationName = "entradaCubo";
    client.send(message);
}
