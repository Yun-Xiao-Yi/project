$(document).ready(function(){
	$(".nav .sub-wrap").css("width",$(window).width());
	$(".linkd li").first().css({"background-position":"left 0px"});
	$(".linkd li").eq(1).css({"background-position":"left -30px"});
	$(".linkd li").eq(2).css({"background-position":"left -60px"});
	$(".linkd li").eq(3).css({"background-position":"left -90px"});
	$(".linkd li").eq(4).css({"background-position":"left -120px"});
	$(".linkd li").eq(5).css({"background-position":"left -150px"});
	$(".linkd li").eq(6).css({"background-position":"left -180px"});
	$(".linkd li").eq(7).css({"background-position":"left -210px"});
	$(".linkd li").last().css({"background-position":"left -240px"});
	$(".linkd li").eq(6).hover(function (){  
            $("#wx").show();  
        },function (){  
            $("#wx").hide();  
        });
	$(".linkd li").eq(7).hover(function (){  
            $("#wb").show();  
        },function (){  
            $("#wb").hide();  
        });
	$(".linkd li").last().hover(function (){  
            $("#wy").show();  
        },function (){  
            $("#wy").hide();  
        });
});

		   
$(document).ready(function(){
  $(".xzxx li").first().css({"background-position":"20px 0px"});
  $(".xzxx li").eq(1).css({"background-position":"20px -62px"}); 
});