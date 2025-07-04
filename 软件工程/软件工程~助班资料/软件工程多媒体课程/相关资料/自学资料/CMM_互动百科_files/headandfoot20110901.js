/**
 * 头部搜索框的事件
 */
var headSearch = {
	searchType : "doc",
	docContant : "doc",
	pictureContant : "tupian",
	articleContant : "wenzhang",
	docEntryClassCache : null,
	// 初始化搜索事件，给搜索按钮，搜索选项菜单和进入词条按钮复制事件
	initSearch : function() {
		headSearch.searchType = "doc";
		if (headSearch.docEntryClassCache == null)
			headSearch.docEntryClassCache = $(".search-panel input[name=q]")
					.attr('class');
		$("a[action='searchselecthref']").bind("click", function() {
			$(this).parents("ul").children("li").removeClass();
			$(this).parent().addClass("selected");
			var searchpanelobj = $(this).parents("ul").next(".search-panel");
			searchpanelobj.children("input[name=q]").attr('class', 'l');
			searchpanelobj.children(".entry-button").hide();
			var selectflag = $(this).attr("selectflag");
			if (selectflag == "article") {
				headSearch.articleSelected($(this));
			} else if (selectflag == "picture") {
				headSearch.pictureSelected($(this));
			} else {
				headSearch.docSelected($(this));
			}
			return false;
		});
		$(".entry-button").bind("click", function() {
			headSearch.docEntry($(this).parent().find("input[name=q]").val());
		});
		$(".search-button").bind("click", function() {
			var qvalue = $(this).parent().find("input[name=q]").val();
			headSearch.searchSubmit(qvalue);
		});
		$(".search-panel input[name=q]").bind("keydown", function(event) {
			if (event.keyCode == 13) {
				if (headSearch.searchType == headSearch.docContant) {
					headSearch.docEntry($(this).val());
				} else {
					headSearch.searchSubmit($(this).val());
				}

			}
		});
	},
	// 选择词条时的搜索栏变化
	docSelected : function(object) {
		headSearch.searchType = headSearch.docContant;
		var searchpanelobj = object.parents("ul").next(".search-panel");
		if (headSearch.docEntryClassCache != null) {
			searchpanelobj.children("input[name=q]").attr('class',
					headSearch.docEntryClassCache);
		}
		searchpanelobj.children(".entry-button").show();
	},
	// 选择文章时的搜索栏变化
	articleSelected : function() {
		headSearch.searchType = headSearch.articleContant;
	},
	// 选择图片时的搜索栏变化
	pictureSelected : function() {
		headSearch.searchType = headSearch.pictureContant;
	},
	// 内容检查
	checkValue : function(qvalue) {
		if (qvalue == null) {
			return "";
		}
		qvalue = qvalue.replace(/(^\s*)|(\s*$)/g, "");
		qvalue = qvalue.replace(/\/|\%|\\/g, "");
		qvalue = qvalue.replace(/\&/g, "%26");
		qvalue = qvalue.replace(/\+/g, "%2B");
		if (qvalue.length > 100) {
			qvalue = qvalue.substring(0, 100);
		}
		if (qvalue == "" || /^(\.)*(\.){1,}(\.)*$/.test(qvalue)) {
			alert("请输入内容");
			return "";
		}
		return qvalue;
	},
	// 进入词条
	docEntry : function(qvalue) {
		qvalue = headSearch.checkValue(qvalue);
		if (qvalue == "") {
			return false;
			;
		} else {
			window.parent.location = "http://www.hudong.com/wiki/"
					+ encodeURIComponent(qvalue)+"&prd=button_doc_jinru";

		}
	},
	// 搜索
	searchSubmit : function(qvalue) {
		qvalue = headSearch.checkValue(qvalue);
		if (qvalue == "") {
			return;
		}
		window.parent.location = "http://so.hudong.com/s/"
				+ headSearch.searchType + "/" + encodeURIComponent(qvalue)+"&prd=button_"+headSearch.searchType+"_search";
	}
};
$(document).ready(function() {
	headSearch.initSearch();
});

function setHomepage()// 设置首页
{
	if (document.all) {
		document.body.style.behavior = 'url(#default#homepage)';
		document.body.setHomePage('http://www.hudong.com');
	} else if (window.sidebar) {
		if (window.netscape) {
			try {
				netscape.security.PrivilegeManager
						.enablePrivilege("UniversalXPConnect");
			} catch (e) {
				alert("抱歉！您的浏览器不支持直接设为首页。请在浏览器地址栏输入“about:config”并回车然后将[signed.applets.codebase_principal_support]设置为“true”，点击“加入收藏”后忽略安全提示，即可设置成功。");
			}
		}
		var prefs = Components.classes['@mozilla.org/preferences-service;1']
				.getService(Components.interfaces.nsIPrefBranch);
		prefs.setCharPref('browser.startup.homepage', 'http://www.hudong.com');
	}
}

function addBookmark(title) { // 设置收藏夹
	var url = parent.location.href;
	if (window.sidebar) {
		window.sidebar.addPanel(title, url, "");
	} else if (document.all) {
		window.external.AddFavorite(url, title);
	} else if (window.opera && window.print) {		return true;
	}
}