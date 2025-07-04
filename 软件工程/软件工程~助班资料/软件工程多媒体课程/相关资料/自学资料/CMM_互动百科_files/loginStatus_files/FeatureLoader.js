

    




if (!window.XN) {
  XN = {};
}
XN.isInKaixinCanvas = function (){
  if (!XN.isInKaixinCanvas._inKaixin) {
    XN.isInKaixinCanvas._inKaixin = (window.parent != window && window.location.href.match("xn_sig_in_iframe=1") != null && window.location.href.match("xn_sig_domain=kaixin.com") != null);
  }
  return XN.isInKaixinCanvas._inKaixin;
}

if (!window.Connect_Config) {
  Connect_Config = {
    "domain": XN.isInKaixinCanvas() ? "kaixin.com" : "renren.com",
    "mainsite_name": XN.isInKaixinCanvas() ? "Kaixin" : "Renren",
    "static_url": "http://a.xnimg.cn",
    "small_static_url": "http://s.xnimg.cn/connect",
    "mainsite_name_cn": XN.isInKaixinCanvas() ? "\u5f00\u5fc3\u7f51" : "\u4eba\u4eba\u7f51"
  };
}

if (!XN.Bootstrap) {
  XN.Bootstrap = {
    requireFeatures : function(features, callback) {
      if (XN.Bootstrap.isXdChannel) {
        return;
      }

      XN.Bootstrap.enqueueFeatureRequest({"features": features,
            "callback": callback,
            "loadedCount": 0});
      if (XN.Bootstrap.FeatureMap) {
        if (XN.FeatureLoader) {
          XN.FeatureLoader.singleton.checkRequestQueue();
        } else {
          XN.Bootstrap.addScript(XN.Bootstrap.FeatureMap["Base"].src);
        }
      }
    },

    ensureInit : function(callback) {
      if (!callback) {
        throw("XN.ensureInit called without a valid callback");
      }

      if (XN.Main &&
          XN.Main.get_initialized &&
          XN.Main.get_initialized().get_isReady() &&
          XN.Main.get_initialized().result) {
        return callback();
      }

      XN.Bootstrap.requireFeatures(XN.Bootstrap.features, function() {
        XN.Main.get_initialized().waitForValue(true, callback);
        });
    },

    init : function(api_key, xd_receiver, appSettings) {
      XN.Bootstrap.requireFeatures(XN.Bootstrap.features, function() {
          if (XN.Main) {
            XN.Main.init(api_key, xd_receiver, appSettings);
          }
        });
    },

    addScript : function(src) {
      var scriptElement;

      var scriptElements = document.getElementsByTagName('script');
      if (scriptElements ) {
        var c = scriptElements.length;
        for (var i = 0; i < c; i++) {
          scriptElement = scriptElements[i];
          if (scriptElement.src == src) {
            return;
          }
        }
      }


      scriptElement = document.createElement("script");
      scriptElement.type = "text/javascript";
      scriptElement.src = src;
      document.getElementsByTagName("HEAD")[0].appendChild(scriptElement);
    },

    initializeXdChannel : function () {
      XN.Bootstrap.isXdChannel =
        window.location.search.indexOf(XN.Bootstrap.xnc_channel_token) >= 0;

      if (!XN.Bootstrap.isXdChannel) {
        XN.Bootstrap.createHiddenDiv();
        XN.Bootstrap.detectDOMContentReady();
      }
    },

    detectDOMContentReady : function() {
      if (window.navigator.userAgent.toLowerCase().indexOf("msie") >= 0) {
        window.attachEvent("onload", function() {
            XN.Bootstrap.IsDomContentReady = true;
          });
      } else {
        window.addEventListener("DOMContentLoaded", function() {
            XN.Bootstrap.IsDomContentReady = true;
          }, false);
      }
    },

    createHiddenDiv : function() {
      if (document.getElementById('XN_HiddenContainer') == null) {
        if (document.body) {
          window.setTimeout(function() {
            var div = document.createElement("div");
            div.id = "XN_HiddenContainer";
            div.style.position = "absolute";
            div.style.top = "-10000px";
            div.style.left = "-10000px";
            div.style.width = "0px";
            div.style.height = "0px";
            document.body.appendChild(div);
          }, 0);
        }
        else {
          document.write('<div id="XN_HiddenContainer" '
                       + 'style="position:absolute; top:-10000px; left:-10000px; width:0px; height:0px;" >'
                       + '</div>');
        }
      }
    },

    loadServerMaps : function(featureMap, staticResourceMap, siteVarsMap) {
      if(!this.FeatureMap.length) {
        this.FeatureMap = featureMap;
        this.StaticResourceVersions = staticResourceMap;
        if (XN.FeatureLoader) {
          XN.FeatureLoader.singleton.checkRequestQueue();
        }
      }
      if (!this.siteVars.length) {
        this.siteVars = siteVarsMap;
      }
    },

    enqueueFeatureRequest : function(request) {
      this.FeatureRequestQueue[this.FeatureRequestQueue.length] = request;
    },

    detectDocumentNamespaces : function() {
      if (document.namespaces && !document.namespaces.item['xn']) {
        document.namespaces.add('xn');
      }
    },

    createDefaultXdChannelUrl : function() {
      var xd_receiver = location.protocol + '//' + location.hostname +
      location.pathname + location.search;
      if(location.search || location.search.length > 0) {
        xd_receiver += '&';
      } else {
        xd_receiver += '?';
      }
      xd_receiver += 'xnc_channel=1';
      return xd_receiver;
    },

    features                 : ["Connect"],

    IsDomContentReady        : false,
    FeatureRequestQueue      : [],
    FeatureMap               : {},
    StaticResourceVersions   : {},
    CustomFeatureMap         : [],
    siteVars                 : {},
    xnc_channel_token        : 'xnc_channel=1'
  };
  window.XN_RequireFeatures        = XN.Bootstrap.requireFeatures;
  window.XN.init                   = XN.Bootstrap.init;
  window.XN.ensureInit             = XN.Bootstrap.ensureInit;
}

XN.Bootstrap.initializeXdChannel();
XN.Bootstrap.detectDocumentNamespaces();
XN.Bootstrap.loadServerMaps(
        /* featureMap */ {
        	"Base":{"src":Connect_Config.small_static_url + "/a22410/js/base.js","dependencies":null},
        	"Common":{"src":Connect_Config.small_static_url + "/a22410/js/base.js","dependencies":["Base"]},
        	"XdComm":{"src":Connect_Config.small_static_url + "/a22410/js/base.js","dependencies":["Common"]},
			"Api":{"src":Connect_Config.small_static_url + "/a19898/js/api.js","dependencies":["XdComm"]},
        	"CanvasUtil":{"src":Connect_Config.small_static_url + "/a16726/js/CanvasUtil.js","dependencies":["XdComm"]},
        	"Connect":{"src":Connect_Config.small_static_url + "/a22410/js/base.js","dependencies":["XdComm"],
        		"styleSheets":[Connect_Config.small_static_url + "/a16474/css/xn_connect.css"]},
			"Connect.Feed":{"src":Connect_Config.small_static_url + "/a18667/js/connect_feed.js","dependencies":["Connect"]},
			"Connect.Share":{"src":Connect_Config.small_static_url + "/a16726/js/connect_share.js","dependencies":["Connect"]},
        	"EXNML":{"src":Connect_Config.small_static_url + "/a16882/js/exnml.js","dependencies":["XdComm"]},
        	"EXNML.LoginButton":{"src":Connect_Config.small_static_url + "/a16882/js/tags/loginbutton.js","dependencies":["EXNML"]},
			"EXNML.Name":{"src":Connect_Config.small_static_url	+ "/a21864/js/tags/name.js","dependencies":["EXNML", "Api"]},
			"EXNML.ProfilePic":{"src":Connect_Config.small_static_url + "/a19898/js/tags/profilepic.js","dependencies":["EXNML", "Api"]},
			"EXNML.Container":{"src":Connect_Config.small_static_url + "/a16474/js/tags/container.js","dependencies":["EXNML"]},
			"EXNML.ServerXnml":{"src":Connect_Config.small_static_url + "/a18666/js/tags/serverxnml.js","dependencies":["EXNML"]},
			"EXNML.ShareButton":{"src":Connect_Config.small_static_url + "/a20036/js/tags/sharebutton.js","dependencies":["EXNML", "Connect.Share"]},
			"EXNML.LiveStream":{"src":Connect_Config.small_static_url + "/a16726/js/tags/live_stream.js","dependencies":["EXNML"]},
			"EXNML.Friendpile":{"src":Connect_Config.small_static_url + "/a16720/js/tags/friendpile.js","dependencies":["EXNML"]},
        	"Expose":{"src":Connect_Config.small_static_url + "/a16722/js/expose.js","dependencies":["Common"]},
        	"CacheData":{"src":Connect_Config.small_static_url + "/a16474/js/CacheData.js","dependencies":["Common","XdComm"]},
        	"Integration":{"src":Connect_Config.small_static_url + "/js/Integration.js?ver=20057","dependencies":["Connect"]},
        	"Comments":{"src":Connect_Config.small_static_url + "/js/Comments.js?ver=20057","dependencies":["XdComm","EXNML"]}},
        /* staticResourceMap */ {"base_url_format":"http:\/\/{0}.connect." + Connect_Config.domain + "\/","loginout_url":"http://login.api." + Connect_Config.domain + "/connect/{0}","api_channel":10000,"api_server":10000,"www_channel":10000,"xd_comm_swf_url":Connect_Config.static_url + "/connect/swf/XNConnect2.1.swf","login_img_dark_small":Connect_Config.static_url + "/connect/img/login_buttons/renren/connect_light_small.png","login_img_dark_medium":Connect_Config.static_url + "/connect/img/login_buttons/renren/connect_dark_medium.png","login_img_dark_large":Connect_Config.static_url + "/connect/img/login_buttons/renren/connect_dark_large.png","login_img_light_small":Connect_Config.static_url + "/connect/img/login_buttons/renren/connect_light_small.png","login_img_light_medium":Connect_Config.static_url + "/connect/img/login_buttons/renren/connect_light_medium.png","login_img_light_large":Connect_Config.static_url + "/connect/img/login_buttons/renren/connect_light_large.png","login_img_white_small":Connect_Config.static_url + "/connect/img/login_buttons/renren/connect_light_small.png","login_img_white_medium":Connect_Config.static_url + "/connect/img/login_buttons/renren/connect_light_medium.png","login_img_white_large":Connect_Config.static_url + "/connect/img/login_buttons/renren/connect_light_large.png","logout_img_small":Connect_Config.static_url + "/connect/img/login_buttons/renren/logout_small.gif","logout_img_medium":Connect_Config.static_url + "/connect/img/login_buttons/renren/logout_medium.gif","logout_img_large":Connect_Config.static_url + "/connect/img/login_buttons/renren/logout_large.gif", "share_img_standard_dark":Connect_Config.static_url + "/connect/img/share_buttons/renren/share_img_standard_dark.png", "share_img_standard_light":Connect_Config.static_url + "/connect/img/share_buttons/renren/share_img_standard_light.png", "expose_close_mark":Connect_Config.static_url + "/connect/img/login_buttons/renren/expose/close_mark.png", "expose_close_mark_mouseover":Connect_Config.static_url + "/connect/img/login_buttons/renren/expose/close_mark_mover.png", "expose_guide":Connect_Config.static_url + "/connect/img/login_buttons/renren/expose/guide.gif", "expose_guide_arrow_left":Connect_Config.static_url + "/connect/img/login_buttons/renren/expose/guide_arrow_left.gif", "expose_guide_arrow_right":Connect_Config.static_url + "/connect/img/login_buttons/renren/expose/guide_arrow_right.gif", "guide_close_mark":Connect_Config.static_url + "/connect/img/login_buttons/renren/expose/guide_close_mark.png", "guide_close_mark_mover":Connect_Config.static_url + "/connect/img/login_buttons/renren/expose/guide_close_mark_mover.png"},
        /* siteVarSettings   */ {"canvas_client_compute_content_size_method":1,"use_postMessage":0, "use_flash": 1, "api_cache_max_age": 600000, "xnml_cache_max_age": 600000, "expose_guide_width": 423, "expose_guide_height": 249, "expose_guide_arrow_width": 28, "expose_guide_arrow_height": 26});

