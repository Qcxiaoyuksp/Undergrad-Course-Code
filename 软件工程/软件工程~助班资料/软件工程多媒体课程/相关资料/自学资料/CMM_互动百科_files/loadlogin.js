function getHdCookie(name){
	var arr = document.cookie.match(new RegExp("(^| )"+name+"=([^;]*)(;|$)"));
	if(arr != null) return unescape(arr[2]); return null;
}

var common_login = {
	inputtime : 0,
	blinkswitch : 0,
	blinktitle : document.title,
	flashMsging : null,
	blinkid : null,
	stopFlashNewMsg:function()
	{
		clearInterval(common_login.blinkid);
		document.title = common_login.blinktitle;
	},
	flashNewMsg : function()
	{
		var now = new Date();
		var nowtime = now.getTime();
		if (nowtime - common_login.inputtime > 5000)
		{
			document.title = common_login.blinkswitch % 2 ? "【　　　】 - " + common_login.blinktitle
					: "【新消息】 - " + common_login.blinktitle;
		}
		common_login.blinkswitch++;
		if(common_login.blinkswitch>50)
		{
			common_login.stopFlashNewMsg();
		}
	},
	setDefaultLoadInfo:function(loginType,tagObject)
	{
		if(common_login.blinkid!=null)
		{
			common_login.stopFlashNewMsg();
		}
		try{
			switch(loginType)
		   {
		   case '2'://(第二版登录头)
			 {
				 tagObject.innerHTML="<li><a href='javascript:void(0)' onclick='setHomepage();'>设为首页</a></li><li class='bor-ld'><a href='javascript:void(0)' onclick='addBookmark(document.title);'>收藏本站</a></li><li id='help'><a href='http://service.hudong.com/'>帮助</a></li><li id='user'><a href='http://passport.hudong.com/user/userRegister.jsp'>注册</a></li><li id='entry'><a onmousedown=\"var date=new Date();date.setTime(date.getTime()+24*3600*1000);document.cookie='nextURL='+encodeURIComponent(document.location.href)+';expire='+date.toGMTString()+';path=/;domain=.hudong.com;'\" href='http://passport.hudong.com/login.do'>登录</a></li>";
				 break;
		     }
		   case '3'://无收藏(第二版登录头)
		     {
		    	 tagObject.innerHTML="<li id='help'><a href='http://service.hudong.com/'>帮助</a></li><li id='user'><a href='http://passport.hudong.com/user/userRegister.jsp'>注册</a></li><li id='entry'><a onmousedown=\"var date=new Date();date.setTime(date.getTime()+24*3600*1000);document.cookie='nextURL='+encodeURIComponent(document.location.href)+';expire='+date.toGMTString()+';path=/;domain=.hudong.com;'\" href='http://passport.hudong.com/login.do'>登录</a></li>";
		    	 break; 
		     }
		   case '5'://只有登陆注册 -2010.10.26(第四版登录头)
		     {
		    	 var loginDom = tagObject;
		    	 	if(loginDom.getElementsByTagName("li")[0].getElementsByTagName("a").length>0)
		    	 	{
		    	 		for ( var i = 0; i < 2; i++)
						{
							loginDom.removeChild(loginDom.getElementsByTagName("li")[0]);
						}
		    	 	}
		    	 	else
		    	 	{
		    	 		loginDom.removeChild(loginDom.getElementsByTagName("li")[0]);
		    	 	}
					var loginNode = document.createElement("li");
					var loginNodeLink = document.createElement("a");
					var spanNodeLink = document.createElement("span");
					var spanNodeLink_2 = document.createElement("span");
					loginNode.setAttribute('id', 'entry');
					loginNodeLink.setAttribute('href','http://passport.hudong.com/login.do');
					loginNodeLink.setAttribute('onmousedown',"document.domain='hudong.com';var date=new Date();date.setTime(date.getTime()+24*3600*1000);document.cookie='nextURL='+encodeURIComponent((document.referrer.length>0&&document.referrer!=window.location.href)?document.referrer:window.location.href)+';expire='+date.toGMTString()+';path=/;domain=.hudong.com;'");
					loginNodeLink.innerHTML = "登录";
					loginNode.appendChild(spanNodeLink);
					loginNode.appendChild(loginNodeLink);
					var exitNode = document.createElement("li");
					var exitNodeLink = document.createElement("a");
					exitNode.setAttribute('id', 'login');
					exitNodeLink.setAttribute('href','http://passport.hudong.com/user/userRegister.jsp');
					exitNodeLink.innerHTML = "免费注册";
					exitNode.appendChild(spanNodeLink_2);
					exitNode.appendChild(exitNodeLink);
					loginDom.insertBefore(loginNode, loginDom.firstChild);
					loginDom.insertBefore(exitNode, loginNode);
		    	 break; 
		     }
		   case '6'://只有登陆注册(iframe调用) -2011.01.17(第四版登录头)
		     {
		    	 	var loginDom = tagObject;
		    	 	if(loginDom.getElementsByTagName("li")[0].getElementsByTagName("a").length>0)
		    	 	{
		    	 		for ( var i = 0; i < 2; i++)
						{
							loginDom.removeChild(loginDom.getElementsByTagName("li")[0]);
						}
		    	 	}
		    	 	else
		    	 	{
		    	 		loginDom.removeChild(loginDom.getElementsByTagName("li")[0]);
		    	 	}
					var loginNode = document.createElement("li");
					var loginNodeLink = document.createElement("a");
					loginNodeLink.setAttribute('target', '_parent');
					var spanNodeLink = document.createElement("span");
					var spanNodeLink_2 = document.createElement("span");
					loginNode.setAttribute('id', 'entry');
					loginNodeLink.setAttribute('href','http://passport.hudong.com/login.do');
					loginNodeLink.setAttribute('onmousedown',"document.domain='hudong.com';var date=new Date();date.setTime(date.getTime()+24*3600*1000);document.cookie='nextURL='+encodeURIComponent(document.referrer)+';expire='+date.toGMTString()+';path=/;domain=.hudong.com;'");
					loginNodeLink.innerHTML = "登录";
					loginNode.appendChild(spanNodeLink);
					loginNode.appendChild(loginNodeLink);
					var exitNode = document.createElement("li");
					var exitNodeLink = document.createElement("a");
					exitNodeLink.setAttribute('target', '_parent');
					exitNode.setAttribute('id', 'login');
					exitNodeLink.setAttribute('href','http://passport.hudong.com/user/userRegister.jsp');
					exitNodeLink.innerHTML = "免费注册";
					exitNode.appendChild(spanNodeLink_2);
					exitNode.appendChild(exitNodeLink);
					loginDom.insertBefore(loginNode, loginDom.firstChild);
					loginDom.insertBefore(exitNode, loginNode);
		    	 break; 
		     }
		   case '7'://-2011.02.23(第五版登录头)
		     {
		    	 var loginDom = tagObject;
		    	 	if(loginDom.getElementsByTagName("li")[0].getElementsByTagName("a").length>0)
		    	 	{
		    	 		for ( var i = 0; i < 3; i++)
						{
							loginDom.removeChild(loginDom.getElementsByTagName("li")[0]);
						}
		    	 	}
		    	 	else
		    	 	{
		    	 		loginDom.removeChild(loginDom.getElementsByTagName("li")[0]);
		    	 	}
					var loginNode = document.createElement("li");
					var loginNodeLink = document.createElement("a");
					var spanNodeLink = document.createElement("span");
					var spanNodeLink_2 = document.createElement("span");
					loginNode.setAttribute('id', 'entry');
					loginNodeLink.setAttribute('href','http://passport.hudong.com/login.do');
					loginNodeLink.setAttribute('target', '_self');
					loginNodeLink.setAttribute('onmousedown',"document.domain='hudong.com';var date=new Date();date.setTime(date.getTime()+24*3600*1000);document.cookie='nextURL='+encodeURIComponent((document.referrer.length>0&&document.referrer!=window.location.href)?document.referrer:window.location.href)+';expire='+date.toGMTString()+';path=/;domain=.hudong.com;'");
					loginNodeLink.innerHTML = "登录";
					loginNode.appendChild(spanNodeLink);
					loginNode.appendChild(loginNodeLink);
					var exitNode = document.createElement("li");
					var exitNodeLink = document.createElement("a");
					exitNode.setAttribute('id', 'login');
					exitNodeLink.setAttribute('href','http://passport.hudong.com/user/userRegister.jsp');
					exitNodeLink.setAttribute('target', '_self');
					exitNodeLink.innerHTML = "免费注册";
					exitNode.appendChild(spanNodeLink_2);
					exitNode.appendChild(exitNodeLink);
					var helpNode = document.createElement("li");
					var helpNodeLink = document.createElement("a");
					helpNode.className='bor-no';
					helpNodeLink.setAttribute('href','http://service.hudong.com/');
					helpNodeLink.innerHTML = "帮助";
					helpNode.appendChild(helpNodeLink);
					loginDom.insertBefore(loginNode, loginDom.firstChild);
					loginDom.insertBefore(exitNode, loginNode);
					loginDom.insertBefore(helpNode, exitNode);
					
					
		    	 break; 
		     }
		   case '8'://-2011.02.23(第五版登录头)
		     {
		    	 var loginDom = tagObject;
		    	 	if(loginDom.getElementsByTagName("li")[0].getElementsByTagName("a").length>0)
		    	 	{
		    	 		for ( var i = 0; i < 3; i++)
						{
							loginDom.removeChild(loginDom.getElementsByTagName("li")[0]);
						}
		    	 	}
		    	 	else
		    	 	{
		    	 		loginDom.removeChild(loginDom.getElementsByTagName("li")[0]);
		    	 	}
					var loginNode = document.createElement("li");
					var loginNodeLink = document.createElement("a");
					var spanNodeLink = document.createElement("span");
					var spanNodeLink_2 = document.createElement("span");
					loginNode.setAttribute('id', 'entry');
					loginNodeLink.setAttribute('href','http://passport.hudong.com/login.do');
					loginNodeLink.setAttribute('target', '_self');
					loginNodeLink.setAttribute('onmousedown',"document.domain='hudong.com';var date=new Date();date.setTime(date.getTime()+24*3600*1000);document.cookie='nextURL='+encodeURIComponent((document.referrer.length>0&&document.referrer!=window.location.href)?document.referrer:window.location.href)+';expire='+date.toGMTString()+';path=/;domain=.hudong.com;'");
					loginNodeLink.innerHTML = "登录";
					loginNode.appendChild(spanNodeLink);
					loginNode.appendChild(loginNodeLink);
					var exitNode = document.createElement("li");
					var exitNodeLink = document.createElement("a");
					exitNode.setAttribute('id', 'login');
					exitNodeLink.setAttribute('href','http://passport.hudong.com/user/userRegister.jsp');
					exitNodeLink.setAttribute('target', '_self');
					exitNodeLink.innerHTML = "免费注册";
					exitNode.appendChild(spanNodeLink_2);
					exitNode.appendChild(exitNodeLink);
					var helpNode = document.createElement("li");
					var helpNodeLink = document.createElement("a");
					helpNode.className='bor-no';
					helpNodeLink.setAttribute('href','http://service.hudong.com/');
					helpNodeLink.innerHTML = "帮助";
					helpNode.appendChild(helpNodeLink);
					loginDom.insertBefore(loginNode, loginDom.firstChild);
					loginDom.insertBefore(exitNode, loginNode);
					loginDom.insertBefore(helpNode, exitNode);
					
					
		    	 break; 
		     }
		   case '9'://-2012.03.23(企业百科头)
		     {
		    	 var loginDom = tagObject;
		    	 loginDom.innerHTML = 
		    		 '<li class="cwhite"><a href="http://passport.hudong.com/user/xbkUserRegister.jsp?userType=company&autourl='+ window.location.href +'">注册</a> | <a href="http://www.baike.com">百科网</a> | <a href="http://qiye.baike.com/contact.html">客服</a></li>'
      					+ '<li><a class="but-qylogin" href="http://passport.hudong.com/login.do?site_ource=xiaobaike_page&amp;service='+ window.location.href +'">企业用户登录</a></li>'
		    	 break;
		     }
		   default://(第一版登录头)
			   tagObject.innerHTML="<li><a href=\"http://service.hudong.com/\" target=\"_blank\" >帮助</a></li><li><a href=\"http://www.hudong.com/tour/tour_1.html\" target=\"_blank\" >快速了解</a>|</li><li></a><a href=\"http://passport.hudong.com/user/userRegister.jsp\">注册</a>|</li><li><a href=\"http://passport.hudong.com/login.do\" onmousedown=\"var date=new Date();date.setTime(date.getTime()+24*3600*1000);document.cookie=\'nextURL=\'+encodeURIComponent(document.location.href)+\';expire=\'+date.toGMTString()+\';path=/;domain=.hudong.com;\'\" >登录</a>|</li>";
		   }
		}catch(e)
		{
			alert('用户数据加载异常');
		}
	},
	loadUserLoginInfo:function(loginType,bindTagId)
	{
		if(loginType==null||bindTagId==null)
		{
			return false;
		}else
		{
			var ele=document.getElementById(bindTagId);
			if(ele==null||ele=="undefined")
			{
				return false;
			}
			if(getHdCookie('hduser')==null)
			{
				common_login.setDefaultLoadInfo(loginType,ele);
			}else
			{
				if(loginType!='0')//无闪动登陆类型(第一版登录头)
				{
					loginType=loginType || (document.getElementById('logintype')==null?1:document.getElementById('logintype').value);
				}
				if(document.getElementById('commonLoginAction')!=null){
					document.getElementById('commonLoginAction').parentNode.removeChild(document.getElementById('commonLoginAction'));
				}
				try
				{
					var head=document.getElementsByTagName('head').item(0); 
					var script=document.createElement('script'); 
					var usermsg = document.getElementById('usermsgcnt');
					var usermsgcnt=(usermsg==null?'0':usermsg.value);
					script.src='http://apps.hudong.com/commonlogin.wiki?Action=showLoginPage&type='+loginType+'&tagId='+bindTagId+'&usermsgcnt='+usermsgcnt+'&t='+Math.random(); 
					script.type='text/javascript';
					script.id="commonLoginAction";
					head.appendChild(script);
				}
				catch(e)
				{
					if(loginType==4)//读取CMS发布头,然后跨越刷页面(第三版登录头)
					{
						$("#"+bindTagId).replaceWith("<div class=\"link_black\" id=\"nav-minitop\"><a href=\"http://www.hudong.com\" target=\"_parent\" class=\"l\"><img src=\"http://www.huimg.cn/public/logo_min.gif\"/></a><ul class=\"r loggingnews\" id=\"loggingnews\"><li id=\"help\"><li id='help'><a href='http://service.hudong.com/'>帮助</a></li><li id='user'><a href='http://passport.hudong.com/user/userRegister.jsp'>注册</a></li><li id='entry'><a onmousedown=\"var date=new Date();date.setTime(date.getTime()+24*3600*1000);document.cookie='nextURL='+encodeURIComponent(document.location.href)+';expire='+date.toGMTString()+';path=/;domain=.hudong.com;'\" href='http://passport.hudong.com/login.do'>登录</a></li></ul></div>");
					}
					else
					{
						common_login.setDefaultLoadInfo(loginType,ele);
					}
				}
			}
		setTimeout('common_login.loadUserLoginInfo(\''+loginType+'\',"'+bindTagId+'")', 180000);
		}
	}
}

function loadLogin(logintype,tagid)
{
	common_login.loadUserLoginInfo(logintype,tagid);
}

function blinkNewMsg()
{
	common_login.flashNewMsg();
}
function stopBlinkNewMsg()
{
	common_login.stopFlashNewMsg();
}
