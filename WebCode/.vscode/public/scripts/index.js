const firebaseConfig = {
  apiKey: "AIzaSyBccmpjwFKTNgY-NTwfh4tubpPLId9yYcM",
  authDomain: "adrf-relay-control.firebaseapp.com",
  databaseURL:
    "https://adrf-relay-control-default-rtdb.asia-southeast1.firebasedatabase.app",
  projectId: "adrf-relay-control",
  storageBucket: "adrf-relay-control.appspot.com",
  messagingSenderId: "620088651346",
  appId: "1:620088651346:web:8a799d088e6e31eafef98b",
};

//------- Initialize Firebase
//const app = initializeApp(firebaseConfig);
//------- Initialize Firebase
firebase.initializeApp(firebaseConfig);

// Elements for sensor readings
//const tempElement = document.getElementById("temp");

$(document).ready(function () {
  var database = firebase.database();
  var Relay1Status;
  var Relay2Status;
  var Relay3Status;
  // var Relay4Status;
  var TemperatureStatus;
  var DrumStatus;
  var WaterStatus;
  //var tempElement = $("#temp");
  //var dbRefTemp = firebase.database().ref().child("temperature");
  //document.getElementById("temperature").style.display = "block";
  // Update page with new readings
  /*
  dbRefTemp.on("value", (snap) => {
    tempElement.innerText = snap.val();
  });
  */

  //var temp_val = childSnapshot.val().temperature;
  //$("#temp").append(temp_val);

  database.ref().on("value", function (snap) {
    Relay1Status = snap.val().Relay1Status;
    Relay2Status = snap.val().Relay2Status;
    Relay3Status = snap.val().Relay3Status;
    //Relay4Status = snap.val().Relay4Status;

    TemperatureStatus = snap.val().TemperatureStatus;
    $("#temp").append(TemperatureStatus);

    WaterStatus = snap.val().WaterStatus;
    $("#waterstatus").append(WaterStatus);

    DrumStatus = snap.val().DrumStatus;
    $("#drumstatus").append(DrumStatus);

    if (Relay1Status == "1") {
      document.getElementById("unact1").style.display = "none";
      document.getElementById("act1").style.display = "block";
    } else {
      document.getElementById("unact1").style.display = "block";
      document.getElementById("act1").style.display = "none";
    }
    if (Relay2Status == "1") {
      document.getElementById("unact2").style.display = "none";
      document.getElementById("act2").style.display = "block";
    } else {
      document.getElementById("unact2").style.display = "block";
      document.getElementById("act2").style.display = "none";
    }
    if (Relay3Status == "1") {
      document.getElementById("unact3").style.display = "none";
      document.getElementById("act3").style.display = "block";
    } else {
      document.getElementById("unact3").style.display = "block";
      document.getElementById("act3").style.display = "none";
    }
  });

  $(".toggle-btn1").click(function () {
    var firebaseRef1 = firebase.database().ref().child("Relay1Status");
    if (Relay1Status == "1") {
      firebaseRef1.set("0");
      Relay1Status = "0";
    } else {
      firebaseRef1.set("1");
      Relay1Status = "1";
    }
  });
  $(".toggle-btn2").click(function () {
    var firebaseRef2 = firebase.database().ref().child("Relay2Status");
    if (Relay2Status == "1") {
      firebaseRef2.set("0");
      Relay2Status = "0";
    } else {
      firebaseRef2.set("1");
      Relay2Status = "1";
    }
  });
  $(".toggle-btn3").click(function () {
    var firebaseRef3 = firebase.database().ref().child("Relay3Status");
    if (Relay3Status == "1") {
      firebaseRef3.set("0");
      Relay3Status = "0";
    } else {
      firebaseRef3.set("1");
      Relay3Status = "1";
    }
  });
});
