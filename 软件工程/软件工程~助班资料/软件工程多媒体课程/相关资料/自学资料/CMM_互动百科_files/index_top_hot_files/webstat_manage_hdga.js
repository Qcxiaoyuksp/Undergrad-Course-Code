function getPageGACode(){
    var myJSONDomainsObject = [{
        "name": "www",
        "gavalue": "1"
    }, {
        "name": "fenlei",
        "gavalue": "68"
    }, {
        "name": "wiki",
        "gavalue": "2"
    }, {
        "name": "wikibar",
        "gavalue": "3"
    }, {
        "name": "group",
        "gavalue": "4"
    }, {
        "name": "kaiyuan",
        "gavalue": "5"
    }, {
        "name": "bbs",
        "gavalue": "15"
    }, {
        "name": "tupian",
        "gavalue": "19"
    }, {
        "name": "paihangbang",
        "gavalue": "20"
    }, {
        "name": "top",
        "gavalue": "24"
    }, {
        "name": "time",
        "gavalue": "25"
    }, {
        "name": "yun",
        "gavalue": "26"
    }, {
        "name": "task",
        "gavalue": "27"
    }, {
        "name": "dajiang",
        "gavalue": "28"
    }, {
        "name": "pic",
        "gavalue": "29"
    }, {
        "name": "gongyi",
        "gavalue": "30"
    }, {
        "name": "bwg",
        "gavalue": "31"
    }, {
        "name": "ceshi",
        "gavalue": "32"
    }, {
        "name": "123",
        "gavalue": "33"
    }, {
        "name": "renwu",
        "gavalue": "34"
    }, {
        "name": "shenghuo",
        "gavalue": "35"
    }, {
        "name": "jingji",
        "gavalue": "36"
    }, {
        "name": "redian",
        "gavalue": "37"
    }, {
        "name": "ziran",
        "gavalue": "38"
    }, {
        "name": "wenhua",
        "gavalue": "39"
    }, {
        "name": "lishi",
        "gavalue": "40"
    }, {
        "name": "shehui",
        "gavalue": "41"
    }, {
        "name": "yishu",
        "gavalue": "42"
    }, {
        "name": "dili",
        "gavalue": "43"
    }, {
        "name": "kexue",
        "gavalue": "44"
    }, {
        "name": "tiyu",
        "gavalue": "45"
    }, {
        "name": "jishu",
        "gavalue": "46"
    }, {
        "name": "reci",
        "gavalue": "49"
    }, {
        "name": "so",
        "gavalue": "51"
    }, {
        "name": "photo",
        "gavalue": "52"
    }, {
        "name": "v",
        "gavalue": "53"
    }, {
        "name": "zt",
        "gavalue": "55"
    }, {
        "name": "jiaoshi",
        "gavalue": "56"
    }, {
        "name": "i",
        "gavalue": "57"
    }, {
        "name": "w",
        "gavalue": "58"
    }, {
        "name": "zutu",
        "gavalue": "59"
    }, {
        "name": "c",
        "gavalue": "60"
    }, {
        "name": "passport",
        "gavalue": "66"
    }];
    
    var _gaValue = "UA-5479642-";
    var _hdDoman = ".hudong.com";
    for (var i = 0; i < myJSONDomainsObject.length; i++) {
        if (window.location.href.indexOf(myJSONDomainsObject[i].name + _hdDoman) > -1) {
            _gaValue = _gaValue + myJSONDomainsObject[i].gavalue;
            return _gaValue;
            break;
        }
    }
    return null;
}

if (window.top.frames.length == window.frames.length) {
    _uacct = getPageGACode();
    if (_uacct != null) {
        var access_host = window.location.host;
        var access_host_end = access_host.indexOf(".hudong.com");
        if (access_host_end > 0) {
            access_host = access_host.substring(0, access_host_end);
        }
        var _gaq = _gaq || [];
        _gaq.push(['_setAccount', _uacct]);
        _gaq.push(['_setDomainName', access_host + '.hudong.com']);
        _gaq.push(['_setCookieTimeout', '86400']);
        _gaq.push(['_addOrganic', 'sogou', 'query']);
        _gaq.push(['_addOrganic', 'soso', 'w']);
        _gaq.push(['_addOrganic', 'yodao', 'q']);
        _gaq.push(['_trackPageview']);
	_gaq.push(['_trackPageLoadTime']);
        (function(){
            var ga = document.createElement('script');
            ga.type = 'text/javascript';
            ga.async = true;
            ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
            var s = document.getElementsByTagName('script')[0];
            s.parentNode.insertBefore(ga, s);
        })();
    }
}
