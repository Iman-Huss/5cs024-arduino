<!DOCTYPE html>
<!-- saved from url=(0044)http://mi-linux.wlv.ac.uk/~1613741/valve.php -->
<html><head><meta http-equiv="Content-Type" content="text/html; charset=UTF-8">

    <title>Valve Control </title>
</head>

<body onload="loadPage();">

<?php
$servername = "mi-linux.wlv.ac.uk";
$username = "";
$password = "abdumaphia123";

// Create connection
$conn = new mysqli($servername, $username, $password);

// Check connection
//if ($conn->connect_error) {
//die("Connection failed: " . $conn->connect_error);
//}
//echo "Connected successfully! ";

$sql = "SELECT * FROM `db1526056`.`LOG`";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    echo "<table><tr><th>Valve ID</th><th>Button Press Time</th><th>Status</th><th>Final Time</th></tr>";
    // output data of each row
    while($row = $result->fetch_assoc()) {
        echo "<tr><td>".$row["vid"]."</td><td>".$row["buttonpresstime"]."</td><td>".$row["vstatus"]."</td><td>".$row["finaltime"]."</td></tr>";
        // Without table:
        //echo " VALVE: " . $row["vid"]. " - DETAILS: " . " Button Press Time: " . $row["buttonpresstime"]. ", Status: " . $row["vstatus"]. ", Final Time: " . $row["finaltime"]. "<br>";
    }
    echo "</table>";
} else {
    echo "0 results.";
}

$conn->close();
?>

/* the above is Mohammed code to control his motor's for the valve */

<h1> Valve Control</h1>
<h4 id="result">This is the site where you can control the valves.</h4>

<script type="text/javascript">

    var siteData = [];
    var zoneData = [];
    var valveData = [];
    var arrayLength = valveData.length;

    function addValve(){
        var x = document.getElementById("valveSelect");
        var option = document.createElement("option");
        option.text = document.getElementById("addValveTB").value;
        x.add(option);
        valveData.push(document.getElementById("addValveTB").value);
        document.getElementById("demo2").innerHTML = valveData;
        var valveArrayLength = valveData.length;
    }

    function addZone(){
        var x = document.getElementById("zoneSelect");
        var option = document.createElement("option");
        option.text = document.getElementById("addValveTB").value;
        x.add(option);
        valveData.push(document.getElementById("addValveTB").value);
        var valveArrayLength = valveData.length;
    }

    function addSite(){
        var x = document.getElementById("siteSelect");
        var option = document.createElement("option");
        option.text = document.getElementById("addValveTB").value;
        x.add(option);
        valveData.push(document.getElementById("addValveTB").value);
        var valveArrayLength = valveData.length;
    }

    function removeValve(){
        var x = document.getElementById("valveSelect");
        x.remove(x.selectedIndex);
    }

    function loadZone(){
        var x = document.getElementById("valveSelect");
        x.remove(x.selectedIndex);
    }

    function deleteAll(){
        localStorage.removeItem("valves");
        localStorage.removeItem("check")  ;
    }

    function loadPage(){
        document.getElementById("demo3").innerHTML = localStorage.getItem("check");


        if (localStorage.getItem("check") === null){
            localStorage.setItem("check", "1");
        }

        else{
            var retrievedData = localStorage.getItem("valves");
            valveData = JSON.parse(retrievedData);
            document.getElementById("demo").innerHTML = valveData;

            var valveArrayLength = valveData.length;

            var valveSel = document.getElementById('valveSelect');
            var zoneSel = document.getElementById('zoneSelect');
            var siteSel = document.getElementById('siteSelect');

            for(var i = 0; i < valveArrayLength; i++){
                var opt = document.createElement('option');
                opt.innerHTML = valveData[i];
                opt.textContent = valveData[i];
                valveSel.appendChild(opt);
            }
        }

    }

    function commit() {
        document.getElementById("demo").innerHTML = valveData;
        document.getElementById("demo2").innerHTML = valveData.length;

        localStorage.setItem("valves", JSON.stringify(valveData));
    }
</script>
<label for="siteSelect"><b>Sites:</b></label>
<select id="siteSelect" multiple="multiple" name="siteName">
    <option value="1">1</option>
    <option value="2">2</option>
    <option value="3">3</option>
    <option value="4">4</option>
</select>

<label for="addsite"><b>Add site:</b></label>
<input type="text" id="addSiteTB" placeholder="Enter site name." name="sitetextbox" required="">
<button type="button">Add site</button>
<button type="button">Remove site</button>
<p></p>

<label for="zoneName"><b>Zones:</b></label>
<select id="zoneSelect" multiple="multiple" name="zoneName">
    <option value="a">a</option>
    <option value="b">b</option>
    <option value="c">c</option>
    <option value="d">d</option>

</select>

<label for="addzone"><b>Add zone:</b></label>
<input type="text" id="addZoneTB" placeholder="Enter zone name." name="zonetextbox" required="">
<button type="button">Add zone</button>
<button type="button">Remove zone</button>
<p></p>

<label for="valveName"><b>Valves:</b></label>
<select id="valveSelect" name="valveName">

    <option></option><option>door</option><option>open</option><option>window</option><option>tester 123</option></select>

<label for="addvalve"><b>Add valve:</b></label>
<input type="text" id="addValveTB" placeholder="Enter valve name." name="valvetextbox" required="">
<button type="button" onclick="addValve()">Add valve</button>
<button type="button" onclick="removeValve()">Remove valve</button>
<button type="button" onclick="commit()">Commit</button>
<button type="button" onclick="deleteAll()">Delete all</button>

<p id="demo">,door,open,window,tester 123</p>
<p id="demo2">Please</p>
<p id="demo3">1</p>

/* The above is willyb's code to control which valve you want*/

<?php
$servername = "mi-linux.wlv.ac.uk";
$username = "1526056";
$password = "mysql123";

$conn = new mysqli($servername, $username, $password);

$sql = "SELECT * FROM `db1526056`.`LOG`";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    echo "<table><tr><th>Valve ID</th><th>Button Press Time</th><th>Status</th><th>Final Time</th></tr>";
    while($row = $result->fetch_assoc()) {
        echo "<tr><td>".$row["vid"]."</td><td>".$row["buttonpresstime"]."</td><td>".$row["vstatus"]."</td><td>".$row["finaltime"]."</td></tr>";
    }
    echo "</table>";
} else {
    echo "0 results.";
}

$conn->close();
?>
/* This is adbu's code to see database logs of when the valves were opened and closed */

</body>

</html>


