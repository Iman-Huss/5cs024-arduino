

$ip = $_SERVER['REMOTE_ADDR'];


$(document).ready(function(){
                $("#valOff").click(function(){
                    $.get($ip, {pin:2}); // execute get request
                });
            });
