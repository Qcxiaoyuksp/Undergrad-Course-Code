(function(){
         _hdCO();
        if (window.top.frames.length == window.frames.length) {
			window.setTimeout(function(){
				FilterLM();
			}, 2000);
        }

})();
(function(){
	var hdClickS = document.createElement('script');
	hdClickS.type = 'text/javascript';
	hdClickS.async = true;
	hdClickS.src = 'http://www.huimg.cn/stat/js/HDClickMonitor20111102.js';
    var s = document.getElementsByTagName('script')[0];
    s.parentNode.insertBefore(hdClickS, s);
})();

function _hdCO() {
	if (window.top.frames.length != window.frames.length) {
		if ( typeof(_hd_virtual_iframe) != "undefined" && _hd_virtual_iframe != null) {
			try {
				StatIframeTraffic(_hd_virtual_iframe);
			}
			catch (e) {
			}
		}		
		return;
	}
	
	if (GetCookie("hd_uid") == null) {
		setCookies("hd_uid", genHDUID(), 365);
	}
	var _hd_refer = document.referrer.replace(/,/g, "%2c");
	if(_hd_refer==""){
		_hd_refer="-";
	}
	var _hd_refer_cookie = GetCookie("hd_referer");
	
	var query = window.location.search.substring();
	if ( _hd_refer_cookie!=null && _hd_refer.match(/\.hudong\.com/) && (!query.match("[?&]hf=")) && (!_hd_refer.match("[?&]hf="))   ){

	}else{
		var _hd_src=judgeTGPage(query);
		if(_hd_src==null){
			_hd_src=judgeTGPage(_hd_refer);
		}
		if(_hd_src!=null ){
			if(_hd_src!=_hd_refer_cookie){			
				setCookies("hd_referer", _hd_src,1);
			}			
		}else{
			setCookies("hd_referer", _hd_refer,1);
		}
	}
	var hd_accessurl = window.location.href.replace(/,/g, "%2c");		

	if (GetCookie("hd_firstaccessurl") == null) {
		setCookies("hd_firstaccessurl", hd_accessurl,1);
	}
	var hd_res = "-";
	try {
		hd_res = getClientRes();
	}
	catch (e) {
	}
	
	var sc = document.createElement("script");
	sc.type = "text/javascript";
	sc.id = "_hdssojs";
	sc.src = "http://stat.hudong.com/hdWebStat.do?random=" + Math.random() + "&hd_accessrefer=" + encodeURIComponent(_hd_refer) + "&hd_accessurl=" + encodeURIComponent(hd_accessurl) + "&hd_res=" + hd_res;
	document.getElementsByTagName("head")[0].appendChild(sc);
}



function setCookies(name, value, day) {
	var d = new Date(); 

	d.setTime(d.getTime() + (day *  86400000 ));
	try{
		document.cookie = name + "=" + value + "; expires=" + d.toGMTString() + "; path=/;domain=.hudong.com";
	}
	catch (e) {
	}
}

function getCookieVal(offset) { 
	var endstr = document.cookie.indexOf(";", offset);
	if (endstr == -1) {
		endstr = document.cookie.length;
	}
	return unescape(document.cookie.substring(offset, endstr));
}
function GetCookie(name) { 
	var arg = name + "=";
	var alen = arg.length;
	var clen = document.cookie.length;
	var i = 0;
	while (i < clen) {
		var j = i + alen;
		if (document.cookie.substring(i, j) == arg) {
			return getCookieVal(j);
		}
		i = document.cookie.indexOf(" ", i) + 1;
		if (i == 0) {
			break;
		}
	}
	return null;
}
function judgeTGPage(query) {
	if (query.indexOf("hf=") < 0) {
		return null;
	}
	//query=query.substring(1);
	var pairs = query.split(/[?&]/);
	var tgPara='hf=';
	if(query.indexOf("pf=") > 0){
		tgPara="pf=";
	}
	for(var i = 0; i < pairs.length; i++) {	
        var pos = pairs[i].indexOf(tgPara);
        if (pos != 0) continue;
        return pairs[i].substring(3); 
    }	
}

function genHDUID() {
	var _hddt = new Date();
	var _hdst = Math.round(_hddt.getTime() / 1000);
	var _hdu = Math.round(Math.random() * 2147483647);
	return _hdu + "" + _hdst;
}

function getClientRes() {
	if (self.screen) {
		sr = screen.width + "x" + screen.height;
	} else {
		if (self.java) {
			var j = java.awt.Toolkit.getDefaultToolkit();
			var s = j.getScreenSize();
			sr = s.width + "x" + s.height;
		}
	}
	return sr;
}
function StatVirtualTraffic(hd_accessrefer, hd_accessurl, hd_virtual) {
	//set screen res
	var hd_res = "-";
	try {
		hd_res = getClientRes();
	}
	catch (e) {
	}
	var sc = document.createElement("script");
	sc.type = "text/javascript";
	sc.id = "_hdsvsojs";
	sc.src = "http://stat.hudong.com/hdWebStatVirtual.do?random=" + Math.random() + "&hd_virtual=" + hd_virtual + "&hd_accessrefer=" + encodeURIComponent(hd_accessrefer) + "&hd_accessurl=" + encodeURIComponent(hd_accessurl) + "&hd_res=" + hd_res;
	document.getElementsByTagName("head")[0].appendChild(sc);
}
function StatIframeTraffic(hd_virtual) {
	if (parent.window.frames.length > 0) {
		var hd_accessrefer = parent.document.referrer;
		var hd_accessurl = parent.window.location;
		StatVirtualTraffic(hd_accessrefer, hd_accessurl, hd_virtual);
	}
}


var _gaq = _gaq || [];
function FilterLM(){
    
    if (judgeLM() == 1) {
        _gaq.push(['_setAccount', 'UA-5479642-64']);
    }
    else {
        _gaq.push(['_setAccount', 'UA-5479642-65']);
    }
    _gaq.push(['_setDomainName', '.hudong.com']);
    _gaq.push(['_setCookieTimeout', '86400']);
    _gaq.push(['_addOrganic', 'sogou', 'query']);
    _gaq.push(['_addOrganic', 'soso', 'w']);
    _gaq.push(['_addOrganic', 'yodao', 'q']);
    _gaq.push(['_trackPageview']);
    (function(){
        var ga = document.createElement('script');
        ga.type = 'text/javascript';
        ga.async = true;
        ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
        var s = document.getElementsByTagName('script')[0];
        s.parentNode.insertBefore(ga, s);
    })();
}

//Filter LM Traffic
function judgeLM(){
    var hdReferFromCookie = GetCookie("hd_referer");
	if(hdReferFromCookie == null || hdReferFromCookie == ""){
		return 0;
	}
	if(hdReferFromCookie.indexOf("lm") == 0){
        return 1;
    }else if(hdReferFromCookie.match(/^(wlgynewtop|qidiannewtop|dlmnewtop|dlmwww|wlgywww|qidianwww|niutop|wlgy|dlm|qidian)$/)){
		return 1;
    }
    return 0;
}

function isLMID(s){
    var patrn = /^[0-9A-Za-z]+$/;
    if (!patrn.exec(s)) {
        return false;
    }
    else {
        return true;
    }
}
