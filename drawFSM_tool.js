var svg;
var radius = 40;
var show_text = "null";
function main(){
	set_svg();//生出SVG畫板
	drawFSM();//呼叫cpp寫出來的js檔
}

function drawState(cx,cy,stateName, color){//畫STATE
	svg.append("circle")
		.attr("id",stateName)
		.attr("r",radius)
		.attr("cx",cx)
		.attr("cy",cy)
		.style("fill", color)
		.style("stroke", "black")
		.style("stroke-width","2");
	svg.append("text").text(stateName)
		.attr("x",cx-radius/2.7)
	    .attr("y",cy+radius/4)
	    .attr("font-size", radius/1.2)
	    .attr("font-family", "Calibri")
	    .attr("fill","black")
	    .attr("padding", "5");
}

function drawTransition(State1,State2,inout,radian){//畫Transition
	var id = State1+"_"+State2;
	
	var x1 = parseInt($("#"+State1).attr("cx"));
	var y1 = parseInt($("#"+State1).attr("cy"));
	var x2 = parseInt($("#"+State2).attr("cx"));
	var y2 = parseInt($("#"+State2).attr("cy"));
	var distanse = Math.sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));

	//線的起點
	var startx = x1 + (x2-x1)*radius/distanse;
	var starty = y1 + (y2-y1)*radius/distanse;
	//線的終點
	var endx = x2 - (x2-x1)*radius/distanse;
	var endy = y2 - (y2-y1)*radius/distanse;
	//線的中點
	var midx = (startx + endx)/2;
	var midy = (starty + endy)/2;
	//向右的法向量
	var r_vector_x = (endy-starty)/distanse*radian;
	var r_vector_y = (endx-startx)/distanse*(-1)*radian;
	//弧線/三角形的中點
	var Qx = midx + r_vector_x*100;
	var Qy = midy + r_vector_y*100;

	svg.append("path")
      .attr("d","M"+startx+" "+starty+" Q"+ Qx +" "+ Qy +","+ endx + " " + endy)//這裡使用的path格式: "M起點 Q三角形頂點,終點"  ex: "M0 0 Q50 50,100 100"
      .attr("fill","none")
      .attr("inout",inout)
      .style("stroke", "#6986B9")
      .style("stroke-width", "3")
      .style("opacity", ".5")
      .attr("marker-end","url(#markerArrow)")
      .on("mouseover", function(){
      	//讓這個物件亮起來並秀出in/out
      	d3.select(this).style("stroke", "#00FF66")
    					 .style("stroke-width", "7");
    	show_text = d3.select(this).attr("inout");
	  })
	  .on("mouseout", function(){
      	//變回來
      	d3.select(this)
      		.style("stroke", "#6986B9")
    		.style("stroke-width", "3");
    	show_text = "null";
    	d3.select("#show_inout_txt").text(show_text)
			.style("display","none");
	  });
}

function set_svg(){//在body中放上svg和箭頭的規則
	//生一個5000*5000的svg畫板
	svg = d3.select("body")
		.append("svg")
		.attr("width",5000)
		.attr("height",5000)
		.on("mousemove",function(){//show in/out
			if(show_text != "null"){
				d3.select("#show_inout_txt").text(show_text)
					.attr("x",d3.event.x + document.body.scrollLeft)
					.attr("y",d3.event.y + document.body.scrollTop)
					.style("display","");
			}
		});

	//箭頭的規則
	svg.append("defs")
		.append("marker")
			.attr("id","markerArrow")
			.attr("markerWidth","8")
			.attr("markerHeight","8")
			.attr("refX","7")
			.attr("refY","5")
			.attr("orient","auto")
			.append("path")
				.attr("d","M2,2 L2,8 L8,5 L2,2")
				.style("fill","#61a8e0");

	svg.append("text")
		.attr("id","show_inout_txt")
		.attr("font-size", 25)
		.attr("font-family", "Calibri")
		.attr("fill","black")
		.style("display","none");
}
window.addEventListener("load", main);//當整個網頁load完時呼叫最上面那個main function