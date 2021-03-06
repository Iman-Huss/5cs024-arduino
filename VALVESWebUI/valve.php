    <!DOCTYPE html>
      	
        
    <HTML>
      	
      <HEAD>
      <H1 id="userinfo">User info</H1>
      <link rel="stylesheet" href="styles.css">
      <TITLE>Valve Control</TITLE> 
      
        
        <LINK href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css" rel="stylesheet"/>
    		<SCRIPT src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></SCRIPT>
    		<SCRIPT src="https://code.jquery.com/jquery-1.12.4.js"></SCRIPT>
    		<SCRIPT src="https://code.jquery.com/ui/1.12.1/jquery-ui.js"></SCRIPT>
    	
      
      	
    
        
        <BODY onload="loadPage()">
        
           <H1> Valve Control</H1>
      	   <H4 id="result" >This is the site where you can control the valves.</H4>
        
    
    <SCRIPT>
    $( function() {
    				$( "#valOn" ).on( "click", function() {
    				  $( "#green" ).toggleClass( "highlightgreen", 1000 );
    				});
    			} );
    
    			$( function() {
    				$( "#valOn" ).on( "click", function() {
            
    					if ($( "#red" ).hasClass( "highlightred" )) {
                  
    					  $( "#red" ).toggleClass( "highlightred", 1000 );
                
                
    					}
    				});
    			} );
    			
    
    			$( function() {
    				$( "#valOff" ).on( "click", function() {
    				  $( "#red" ).toggleClass( "highlightred", 1000 );
    				});
    			} );
    
    			
    			$( function() {
    				$( "#valOff" ).on( "click", function() {
    					if ($( "#green" ).hasClass( "highlightgreen" )) {
    					  $( "#green" ).toggleClass( "highlightgreen", 1000 );
    					}
    				});
    			} );
    
    				
    			$(document).ready(function(){
    				$("#valOff").click(function(){
    					$.get("http://192.168.137.186", {pin:2}); // execute get request
              alert("CLOSING VALVE");
    				});
    			});
    			
    
    				
    			$(document).ready(function(){
    				$("#valOn").click(function(){
    					$.get("http://192.168.137.186", {pin:1}); // execute get request
              alert("OPENING VALVE");
    				});
    			});
    
    		
    
    
    
      var siteData = [];
      var zoneData = [];
      var valveData = [];  
      var arrayLength = valveData.length;   
      
      
    
      
      function addValve() 
      
      {  
          var x = document.getElementById("valveSelect");
          var option = document.createElement("option");
          option.text = document.getElementById("addValveTB").value;
          x.add(option);
          valveData.push(document.getElementById("addValveTB").value);
          document.getElementById("demo2").innerHTML = valveData;
          var valveArrayLength = valveData.length;  
          
      }
      
        function addZone() 
      
      {  
          var x = document.getElementById("zoneSelect");
          var option = document.createElement("option");
          option.text = document.getElementById("addValveTB").value;
          x.add(option);
          valveData.push(document.getElementById("addValveTB").value);
          var valveArrayLength = valveData.length;  
          
      }
      
        function addSite() 
      
      {  
          var x = document.getElementById("siteSelect");
          var option = document.createElement("option");
          option.text = document.getElementById("addValveTB").value;
          x.add(option);
          valveData.push(document.getElementById("addValveTB").value);
          var valveArrayLength = valveData.length;  
          
      }
      
      
    
      function removeValve() {
          var x = document.getElementById("valveSelect");
          x.remove(x.selectedIndex);
          
      }
      
      function loadZone() {
          var x = document.getElementById("valveSelect");
          x.remove(x.selectedIndex);
      }
         
      function deleteAll() {
          localStorage.removeItem("valves");
          localStorage.removeItem("check")  ;
      }
      
      
      
      function loadPage() {
            document.getElementById("demo3").innerHTML = localStorage.getItem("check");
            
      
           if (localStorage.getItem("check") === null) 
           {
              localStorage.setItem("check", "1");   
           }
          
          else
          {
          
          var retrievedData = localStorage.getItem("valves"); 
          valveData = JSON.parse(retrievedData);
          document.getElementById("demo").innerHTML = valveData;
          
          var x = document.getElementById("valveSelect");
          var option = document.createElement("option");
          option.text = localStorage.getItem("valves");
          x.add(option);
          
          
          x.add(option);
          uname = localStorage.getItem("username") ;
          document.getElementById("userinfo").innerHTML = uname;; 
          
            
          var valveArrayLength = valveData.length;
          
             
             
          
          
        var valveSel = document.getElementById('valveSelect');
        var zoneSel = document.getElementById('zoneSelect');
        var siteSel = document.getElementById('siteSelect');
        
        
        for(var i = 0; i < valveArrayLength; i++) 
        {
          
          var opt = document.createElement('option');
          opt.innerHTML = valveData[i];
          opt.textContent = valveData[i];
          valveSel.appendChild(opt);
        }
           
      }    
           
          
      function showLoginInfo()
      {
          localStorage.setItem("username", uname);  
          
          document.getElementById("userinfo").innerHTML = uname;
      }
          
          
      }
      
      function commit()
      {    
          
          
          document.getElementById("demo").innerHTML = valveData;
          document.getElementById("demo2").innerHTML = valveData.length;
          
          localStorage.setItem("valves", JSON.stringify(valveData));
      }   
      

      
    
    
            
      
      
      var modal = document.getElementById("id01");
    
    // When the user clicks anywhere outside of the modal, close it
    window.onclick = function(event) {
        if (event.target == modal) {
            modal.style.display = "none";
        }
    }
    </SCRIPT>
    
    </HEAD>
    
    <BODY>
    
    <DIV class="row">
    			<DIV class="col-sm-12 text-center" >
    				<BUTTON id="valOn" class="btn btn-primary btn-md center-block" Style="width: 250px;" OnClick="btnSearch_Click" >OPEN VALVE</BUTTON>
    				<BUTTON id="valOff" class="btn btn-danger btn-md center-block" Style="width: 250px;" OnClick="btnClear_Click" >CLOSE VALVE</BUTTON>
             <p></p>
             <p></p>
             <p></p>
            <LABEL for="choiceValve"><B>Valve:</B></LABEL>
            
            <SELECT id="choiceValve" name="choiceValveName">
              <OPTION value="a">1</OPTION>
      		    <OPTION value="b">2</OPTION>
      		    <OPTION value="c">3</OPTION>
      		    <OPTION value="d">4</OPTION>
            </SELECT>
    			 </DIV>
    		</DIV>
    
    		<DIV class="container">
    			<DIV class="led-box">
    				<DIV id="green" class="led-green"></DIV>
    				<P>Green LED</P>
    			</DIV>
    			<DIV class="led-box">
    				<DIV id="yellow" class="led-yellow"></DIV>
    				<P>Yellow LED</P>
    			</DIV>
    			<DIV class="led-box">
    				<DIV id="red" class="led-red"></DIV>
    				<P>Red LED</P>
    			</DIV>
    		</DIV>
        
           <DIV class = "col-sm-12 text-center">
          <LABEL for="siteSelect" ><B>Sites:</B></LABEL>
        <SELECT id="siteSelect" name="siteName">  
      		<OPTION value="1">1</OPTION>
      		<OPTION value="2">2</OPTION>
      		<OPTION value="3">3</OPTION>
      		<OPTION value="4">4</OPTION>   
                  
          </SELECT>
          
          <LABEL for="addsite" ><B>Add site:</B></LABEL>
          <INPUT type="text" id="addSiteTB" placeholder="Enter site name." name="sitetextbox" required>
          <BUTTON type="button" >Add site</BUTTON> 
          <BUTTON type="button">Remove site</BUTTON> 
          <P></P>
          
          <LABEL for="zoneName" ><B>Zones:</B></LABEL>
        <SELECT id="zoneSelect" name="zoneName">
      		<OPTION value="a">a</OPTION>
      		<OPTION value="b">b</OPTION>
      		<OPTION value="c">c</OPTION>
      		<OPTION value="d">d</OPTION>
          
        </SELECT>
          
          <LABEL for="addzone" ><B>Add zone:</B></LABEL>
          <INPUT type="text" id="addZoneTB" placeholder="Enter zone name." name="zonetextbox" required>
          <BUTTON type="button">Add zone</BUTTON>
          <BUTTON type="button">Remove zone</BUTTON> 
          <P></P>
          
          <LABEL for="valveName" ><B>Valves:</B></LABEL>
        <SELECT id="valveSelect" name="valveName">
          <OPTION value="a">1</OPTION>
      		<OPTION value="b">2</OPTION>
      		<OPTION value="c">3</OPTION>
      		<OPTION value="d">4</OPTION>
      	
        </SELECT>
        
          <LABEL for="addvalve" ><B>Add valve:</B></LABEL>
          <INPUT type="text" id="addValveTB" placeholder="Enter valve name." name="valvetextbox" required>
          <BUTTON type="button" onclick="addValve()">Add valve</BUTTON>
          <BUTTON type="button" onclick="removeValve()">Remove valve</BUTTON> 
          <p></p>
          <p></p>
          <BUTTON type="button" onclick="commit()">Commit</BUTTON>
          <BUTTON type="button" onclick="deleteAll()">Delete all</BUTTON>
          
          <P id="demo">Here is some text</P>
          <P id="demo2">Please</P>
          <P id="demo3">Please</P>  
        
          
          
          </DIV>
          
      <?php
          $servername = "mi-linux.wlv.ac.uk";
          $username = "1526056";
          $password = "mysql123";
          $databasename = "db1526056";
          
          $conn = new mysqli($servername, $username, $password, $databasename);
          
          $sql = "SELECT * FROM `Log`";
          $result = $conn->query($sql);
          
          if ($result->num_rows > 0) {
              echo "<table><tr><th>Valve ID</th><th>Button Press Time</th><th>Status</th><th>Final Time</th></tr>";
              while($row = $result->fetch_assoc()) {
                  echo "<tr><td>".$row["valveid"]."</td><td>".$row["buttonpresstime"]."</td><td>".$row["vstatus"]."</td><td>".$row["finaltime"]."</td></tr>";
              }
              echo "</table>";
          } else {
              echo "0 results.";
          }
          
          $conn->close();
        ?>
        
        
<?php
$var1 = $_GET['will'];

$fileContent = "Message: ".$var1."\n";


$fileStatus = file_put_contents('abcdefg.txt',$fileContent,FILE_APPEND);
if($fileStatus != false)
{
    echo "SUCCESS: data written to the file";
   
}
else
{
    echo "FAIL: could not write to file";
}  
?> 
  
                
          
      	</BODY>
        
      </HTML>
      	
      