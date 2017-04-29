

<html>
<head>
	<title></title>
	<script src="https://code.jquery.com/jquery-3.2.1.js" integrity="sha256-DZAnKJ/6XZ9si04Hgrsxu/8s717jcIzLy3oi35EouyE=" crossorigin="anonymous"></script>

	<script src="blockly_compressed.js"></script>
	<script src="blocks_compressed.js"></script>
	<script src="msg/js/en.js"></script>
	<script src="arduino_compressed.js"></script>
</head>
<body>
	<div id="blocklyDiv" style="height: 480px; width: 600px; float:left"></div>
	<div id="textarea" style="height: 480px; width: 600px; float:left"></div>
	<input type="submit" value="save" id="save" onclick="savetext()">
	<xml id="toolbox" style="display: none">
	  <category name="Control">
	    <block type="controls_if"></block>
	    <block type="controls_whileUntil"></block>
	    <block type="controls_for">
	  </category>
	  <category name="Logic">
	    <block type="logic_compare"></block>
	    <block type="logic_operation"></block>
	    <block type="logic_boolean"></block>
	  </category>
	  <category name="Robots">
	    <block type="read_digital_input"></block>
	  </category>
	</xml>
	<script>
	  var workspace = Blockly.inject('blocklyDiv',
	      {toolbox: document.getElementById('toolbox')});
	  var code = Blockly.Arduino.workspaceToCode(workspace);

	  function myUpdateFunction(event) {
		  var code = Blockly.Arduino.workspaceToCode(workspace);
		  // alert(code);
		  document.getElementById('textarea').innerHTML = code;
		}
		workspace.addChangeListener(myUpdateFunction);
	</script>

	<script type="text/javascript">
	function savetext() {
        var bufferId = document.getElementById('textarea').textContent;
        $.ajax({
            url:'built.php',
            data:{id : bufferId},
            type:'POST',
            success:function(data){
                console.log(data);
               
            },
            error:function(data){
                
            }
        });
	}
   
	</script>
</body>
</html>
