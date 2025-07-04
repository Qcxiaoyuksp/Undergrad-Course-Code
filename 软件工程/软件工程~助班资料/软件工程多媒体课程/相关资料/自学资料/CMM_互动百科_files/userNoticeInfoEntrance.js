/*
 * 用户各种通知信息页面显示入口，封装了www.huimg.cn/sns/js/userNoticeInfo20110721.js的操作
 * Copyright 2011, Hudong.com
 * author: zhangjuanli
 * editor: hcp000
 * $Date: 2011-07-12 $
 * $Last: 2011-09-07 $
 */
/*
 * 使用说明：
 * 用户可以自定义 var HD_HEAD_OPTION = { }; 该段定义需要在引入js前加载。
	默认配置为
	HD_HEAD_OPTION = {
		divId : "sns-remind",
		location : $(document.body),
		hrefType : "_blank"
	};
	ex. var HD_HEAD_OPTION = {hrefType : "_blank"};
 */
(function(){var b=[];function a(c){var e="http://www.huimg.cn/sns/js/userNoticeInfo20110721.js?20110908";var f=(typeof c=="function")?c:function(){};if(b[e]){f()}else{var d=document.createElement("script");d.src=e;d.type="text/javascript";d.onreadystatechange=function(){if(d.readyState=="complete"||d.readyState=="loaded"){setTimeout(function(){b[e]=true;f()},1000)}};d.onload=function(){setTimeout(function(){b[e]=true;f()},1000)};document.getElementsByTagName("head").item(0).appendChild(d)}}if((typeof jQuery=="undefined")?false:true){$(document).ready(function(){var d={};if(!((typeof HD_HEAD_OPTION)=="undefined")){d=HD_HEAD_OPTION}else{if(window.location.hostname=="i.hudong.com"){d={hrefType:"_self"}}}function c(){var f=["newFansCount","unReadNoticeCount","newFeedMeCount","unReadPrivateMsgCount","unReadNewSystemCount","newRecommendMissionCount","unReadBaikeNoticeCount","unReadCommentReplyNoticeCount","unReadAuthorityAuditCount","teamApplyUserCount"];var e={newFansCount:"<li id='sns_new_fans_count' key='newFansCount'><strong>$</strong>个新粉丝，<a href='http://i.hudong.com/fansList.do'>打个招呼去</a>。</li>",unReadNoticeCount:"<li id='sns_reply_count' key='unReadNoticeCount'><strong>$</strong>条新回复，<a href='http://i.hudong.com/unReadNotice.do'>查看最新回复</a>。</li>",newFeedMeCount:"<li id='sns_new_feed_me_count' key='newFeedMeCount'><strong>$</strong>条新鲜事提到我，<a href='http://i.hudong.com/home.do?type=2'>查看@我的</a>。</li>",unReadPrivateMsgCount:"<li id='sns_private_msg_count' key='unReadPrivateMsgCount'><strong>$</strong>封新的站内信，<a href='http://i.hudong.com/myMsgs.do'>马上查看</a>。</li>",unReadNewSystemCount:"<li id='sns_system_msg_count' key='unReadNewSystemCount'><strong>$</strong>个系统通知，<a href='http://i.hudong.com/myMsgs.do?action=inbox&msg_type=1'>马上查看</a>。</li>",newRecommendMissionCount:"<li id='sns_new_mission_count' key='newRecommendMissionCount'>您有新的推荐任务，<a href='http://i.hudong.com/myMissions.do?showType=2'>马上查看</a>。</li>",unReadBaikeNoticeCount:"<li id='sns_baike_notice_count' key='unReadBaikeNoticeCount'><strong>$</strong>条小百科回复，<a href='http://i.hudong.com/myMsgs.do?action=baikeNotice'>查看最新回复</a>。</li>",unReadCommentReplyNoticeCount:"<li id='sns_comment_reply_notice_msg_count' key='unReadCommentReplyNoticeCount'><strong>$</strong>条新讨论回复，<a href='http://i.hudong.com/myMsgs.do?action=inbox&msg_type=1'>查看最新回复</a>。</li>",unReadAuthorityAuditCount:"<li id='sns_authority_audit_count' key='unReadAuthorityAuditCount'><strong>$</strong>个新权威评审待处理，<a href='http://i.hudong.com/myDocs.do?haveLook=true'>去查看</a>。</li>",teamApplyUserCount:"<li id='mission_team_apply_count' key='teamApplyUserCount'><strong>$</strong>个抢词夺礼入队申请，<a href='http://i.hudong.com/myMissions.do'>马上处理</a>。</li>"};a(function(){try{userNoticeDataInfo.setNoticeKeys(f);userNoticeDataInfo.setNoticeUrl(e);userNoticeDataInfo.initHD(d)}catch(g){}})}setTimeout(function(){c()},1000);setInterval(function(){c()},120000)})}})();