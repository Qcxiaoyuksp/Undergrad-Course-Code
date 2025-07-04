<%--
  Created by IntelliJ IDEA.
  User: 张清晨
  Date: 2023/12/10
  Time: 20:13
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>注册界面</title>
	<meta http-equiv="X-UA-Compatible" content="IE=Edge,chrome=1">
	<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0">
	<link rel="stylesheet" href='https://t1.chei.com.cn/common/ch/iconfont.css'/>
	<link rel="stylesheet" href='https://t1.chei.com.cn/common/plugins/dialog/6.0.5/css/ui-dialog.css'>
	<link rel="stylesheet" href='https://t2.chei.com.cn/account/css/custom/account-1.0.5.css?20230221'>
	<script src="https://t1.chei.com.cn/common/jquery/2.1.1/jquery.min.js"></script>
	<script src="https://t1.chei.com.cn/common/jquery/3.6.0/jquery-migrate-1.2.1.min.js"></script>
	<script src="https://t1.chei.com.cn/common/plugins/validation/jquery.validate.min.js"></script>
	<script src='https://t4.chei.com.cn/account/js/account/jqueryloading-1.0.3.js'></script>
	<script src='https://t3.chei.com.cn/account/js/common/wap.js'></script>
	<script async src="https://www.googletagmanager.com/gtag/js?id=UA-100524-4"></script>
	<script>
        window.dataLayer = window.dataLayer || [];
        function gtag(){dataLayer.push(arguments);}
        gtag('js', new Date());
        gtag('config', 'UA-100524-4', {'sample_rate': 5});
	</script>
</head>
<body>
<div class="outer-layer">
	<div class="outer-layer-content">
		<div class="header">
			<div class="wrap1180 clearfix">
				<div class="location">注册</div>
				<div class="user-info">
					<a class="login-link" href="http://localhost:8080/login.jsp">登录</a>
					<span class="pc-none">&ensp;</span>>
				</div>
			</div>
		</div>
		<link rel="stylesheet" href='https://t1.chei.com.cn/common/js/poshytip/tip-yellow/tip-yellow.css' media="screen" />
		<style>
            .tip-yellow{ background-color: #fef9d9 !important;}
            .tip-yellow .tip-arrow-top{ background-image: url('https://t1.chei.com.cn/common/js/poshytip/tip-yellow/tip-yellow_arrows.png') !important; }
		</style>
		<div class="bg">
			<div class="innter-container">
				<form id="user_reg_fm" name="user_reg_fm" action="/account?method=register" method="post" autocomplete="off">
					<table>
						<tr>
							<th width="295">&nbsp;</th>
							<th width="106"><span class="required">*</span>姓名</th>
							<td colspan="2">
								<input type="text" name="userFullname" value="" id="userFullname" class="smzc-input" placeholder="请填写您的姓名" autocomplete="off"/>
							</td>
							<%--<td class="validate-tips" colspan="3" id='msg1'>--%>
							<%--	请填写规范的姓名。--%>
							<%--</td>--%>
						</tr>
						<tr>
							<th width="295">&nbsp;</th>
							<th width="106"><span class="required"></span>性别</th>
							<td colspan="2"><label for="userGender"></label>
								<input type="radio" checked value="男" class="gender" name="userGender"> 男
								&nbsp;&nbsp;&nbsp;
								<input type="radio" value="女" class="gender" name="userGender"> 女

								<%--<select name="userGender" id="userGender" value="" class="smzc-input" autocomplete="off">--%>
								<%--	<option value=""></option>--%>
								<%--	<option value="女">女</option>--%>
								<%--	<option value="男">男</option>--%>
								<%--	<option value="其它">其它</option>--%>
								<%--</select>--%>
							</td>
							<%--    <div class="col-sm-9">--%>
							<%--        <input type="radio" checked value="男" class="gender"--%>
							<%--               name="gender"> 男--%>
							<%--        &nbsp;&nbsp;&nbsp;<input type="radio" value="女" class="gender"--%>
							<%--                                 name="gender"> 女--%>
							<%--    </div>--%>

							<%--<td class="validate-tips" colspan="3" id='msg2'>--%>
							<%--	跨性别者请选择“其它”选项。--%>
							<%--</td>--%>
						</tr>
						<tr>
							<th width="295">&nbsp;</th>
							<th width="106"><span class="required"></span>民族</th>
							<td colspan="2"><label for="userNation"></label>
								<select name="userNation" id="userNation" value="" class="smzc-input" autocomplete="off">
									<option value=""></option>
									<option value="汉族">汉族</option>
									<option value="阿昌族">阿昌族</option>
									<option value="白族">白族</option>
									<option value="保安族">保安族</option>
									<option value="布朗族">布朗族</option>
									<option value="布依族">布依族</option>
									<option value="朝鲜族">朝鲜族</option>
									<option value="达斡尔族">达斡尔族</option>
									<option value="傣族">傣族</option>
									<option value="德昂族">德昂族</option>
									<option value="东乡族">东乡族</option>
									<option value="侗族">侗族</option>
									<option value="独龙族">独龙族</option>
									<option value="俄罗斯族">俄罗斯族</option>
									<option value="鄂伦春族">鄂伦春族</option>
									<option value="鄂温克族">鄂温克族</option>
									<option value="高山族">高山族</option>
									<option value="仡佬族">仡佬族</option>
									<option value="哈尼族">哈尼族</option>
									<option value="哈萨克族">哈萨克族</option>

									<option value="赫哲族">赫哲族</option>
									<option value="回族">回族</option>
									<option value="基诺族">基诺族</option>
									<option value="京族">京族</option>
									<option value="景颇族">景颇族</option>
									<option value="柯尔克孜族">柯尔克孜族</option>
									<option value="拉祜族">拉祜族</option>
									<option value="黎族">黎族</option>
									<option value="傈僳族">傈僳族</option>
									<option value="珞巴族">珞巴族</option>
									<option value="满族">满族</option>
									<option value="毛南族">毛南族</option>
									<option value="门巴族">门巴族</option>
									<option value="蒙古族">蒙古族</option>
									<option value="苗族">苗族</option>
									<option value="仫佬族">仫佬族</option>
									<option value="纳西族">纳西族</option>
									<option value="怒族">怒族</option>
									<option value="普米族">普米族</option>
									<option value="羌族">羌族</option>
									<option value="撒拉族">撒拉族</option>
									<option value="畲族">畲族</option>
									<option value="水族">水族</option>
									<option value="塔吉克族">塔吉克族</option>
									<option value="塔塔尔族">塔塔尔族</option>
									<option value="土家族">土家族</option>
									<option value="土族">土族</option>
									<option value="佤族">佤族</option>
									<option value="维吾尔族">维吾尔族</option>
									<option value="乌孜别克族">乌孜别克族</option>
									<option value="锡伯族">锡伯族</option>
									<option value="瑶族">瑶族</option>
									<option value="彝族">彝族</option>
									<option value="裕固族">裕固族</option>
									<option value="藏族">藏族</option>
									<option value="壮族">壮族</option>
								</select>
							</td>
							<%--<td class="validate-tips" colspan="3" id='msg3'>--%>
							<%--	请填写户籍上的民族。--%>
							<%--</td>--%>
						</tr>
						<tr>
							<th width="295">&nbsp;</th>
							<th width="106"><span class="required"></span>出生日期</th>
							<td colspan="2">
								<input type="date" name="userBirth" id="userBirth" value="" class="smzc-input" autocomplete="off"/></td>
							<%--<td class="validate-tips" colspan="3" id='msg4'>--%>
							<%--	请填写户籍上的出生日期。--%>
							<%--</td>--%>
						</tr>
						<tr>
							<th width="295">&nbsp;</th>
							<th width="106"><span class="required"></span>文化程度</th>
							<td colspan="2"><label for="educationLevel"></label>
								<select name="educationLevel" id="educationLevel" value="" class="smzc-input" autocomplete="off">
									<option value=""></option>
									<option value="研究生">研究生</option>
									<option value="大学本科">大学本科</option>
									<option value="大学专科和专科学校">大学专科和专科学校</option>
									<option value="中等专业学校或中等技术学校">中等专业学校或中等技术学校</option>
									<option value="技工学校">技工学校</option>
									<option value="高中">高中</option>
									<option value="初中">初中</option>
									<option value="小学">小学</option>
									<option value="文盲或半文盲">文盲或半文盲</option>
								</select></td>
							<%--<td class="validate-tips" colspan="3" id='msg5'>--%>
							<%--	请如实填写。--%>
							<%--</td>--%>
						</tr>
						<tr>
							<th width="295">&nbsp;</th>
							<th width="106"><span class="required"></span>学位</th>
							<td colspan="2"><label for="academicDegree"></label>
								<select name="academicDegree" id="academicDegree" value="" class="smzc-input" autocomplete="off">
									<option value=""></option>
									<option value="学士学位">学士学位</option>
									<option value="硕士学位">硕士学位</option>
									<option value="博士学位">博士学位</option>
								</select></td>
							<%--<td class="validate-tips" colspan="3" id='msg6'>--%>
							<%--	选填。--%>
							<%--</td>--%>
						</tr>
						<tr>
							<th width="295">&nbsp;</th>
							<th width="106"><span class="required"></span>职称</th>
							<td colspan="2"><label for="academicTitle"></label>
								<select name="academicTitle" id="academicTitle" value="" class="smzc-input" autocomplete="off">
									<option value=""></option>
									<option value="教授">教授</option>
									<option value="副教授">副教授</option>
									<option value="讲师">讲师</option>
									<option value="助教">助教</option>
								</select></td>
							<%--<td class="validate-tips" colspan="3" id='msg7'>--%>
							<%--	选填。--%>
							<%--</td>--%>
						</tr>
						<tr>
							<th width="295">&nbsp;</th>
							<th width="106"><span class="required">*</span>专业</th>
							<td colspan="2">
								<input type="text" name="userSpeciality" value="" id="userSpeciality" class="smzc-input" placeholder="请填写您的专业" autocomplete="off"/>
							</td>
						</tr>
						<%--<tr>--%>
						<%--	<th width="106"><span class="required">*</span>专业</th>--%>
						<%--	<td colspan="2"><label for="userSpeciality"></label>--%>
						<%--		<select name="userSpeciality" id="userSpeciality" value="" class="smzc-input" autocomplete="off">--%>
						<%--			<option value=""></option>--%>
						<%--			<option value="哲学">哲学</option>--%>
						<%--			<option value="逻辑学">逻辑学</option>--%>
						<%--			<option value="宗教学">宗教学</option>--%>
						<%--			<option value="伦理学">伦理学</option>--%>
						<%--			<option value="法学">法学</option>--%>
						<%--			<option value="历史学">历史学</option>--%>
						<%--			<option value="考古学">考古学</option>--%>
						<%--			<option value="数学">数学</option>--%>
						<%--			<option value="化学">化学</option>--%>
						<%--			<option value="物理学">物理学</option>--%>
						<%--			<option value="地质学">地质学</option>--%>
						<%--			<option value="天文学">天文学</option>--%>
						<%--		</select></td>--%>
						<%--	<td class="validate-tips" colspan="3" id='msg8'>--%>
						<%--		请如实填写。--%>
						<%--	</td>--%>
						<%--</tr>--%>
						<tr>
							<th width="295">&nbsp;</th>
							<th width="106"><span class="required">*</span>毕业学校</th>
							<td colspan="2">
								<input type="text" name="educationSchool" value="" id="educationSchool" class="smzc-input" placeholder="请填写您的毕业学校" autocomplete="off"/>
							</td>
						</tr>
						<%--<tr>--%>
						<%--	<th width="106"><span class="required">*</span>毕业学校</th>--%>
						<%--	<td colspan="2"><label for="educationSchool"></label>--%>
						<%--		<select name="educationSchool" id="educationSchool"  value="" class="smzc-input" autocomplete="off">--%>
						<%--			<option value=""></option>--%>
						<%--			<option value="北京大学">北京大学</option>--%>
						<%--			<option value="中国科学技术大学">中国科学技术大学</option>--%>
						<%--			<option value="吉林大学">吉林大学</option>--%>
						<%--			<option value="南开大学">南开大学</option>--%>
						<%--			<option value="中山大学">中山大学</option>--%>
						<%--		</select></td>--%>
						<%--	<td class="validate-tips" colspan="3" id='msg9'>--%>
						<%--		请如实填写。--%>
						<%--	</td>--%>
						<%--</tr>--%>
						<tr>
							<th width="295">&nbsp;</th>
							<th width="106"><span class="required"></span>毕业时间</th>
							<td colspan="2">
								<input type="date" name="educationTime" value="" id="educationTime" class="smzc-input" autocomplete="off"/>
							</td>
							<%--<td class="validate-tips" colspan="3" id='msg10'>--%>
							<%--	选填。--%>
							<%--</td>--%>
						</tr>
						<tr>
							<th width="295">&nbsp;</th>
							<th width="106"><span class="required">*</span>所在部门</th>
							<td colspan="2">
								<input type="text" name="department" value="" id="department" class="smzc-input" placeholder="请填写您所在的部门" autocomplete="off"/>
							</td>
						</tr>
						<%--<tr>--%>
						<%--	<th width="106"><span class="required"></span>所在部门</th>--%>
						<%--	<td colspan="2"><label for="department"></label>--%>
						<%--		<select name="department" id="department" value="" class="smzc-input" autocomplete="off">--%>
						<%--			<option value=""></option>--%>
						<%--			<option value="办公室">办公室</option>--%>
						<%--			<option value="宣传部">宣传部</option>--%>
						<%--			<option value="组织部">组织部</option>--%>
						<%--			<option value="纪检监察室">纪检监察室</option>--%>
						<%--			<option value="学工部">学工部</option>--%>
						<%--			<option value="工会">工会</option>--%>
						<%--			<option value="人事部">人事部</option>--%>
						<%--			<option value="教务处">教务处</option>--%>
						<%--			<option value="财务处">财务处</option>--%>
						<%--			<option value="设备处">设备处</option>--%>
						<%--			<option value="科研处">科研处</option>--%>
						<%--			<option value="审计处">审计处</option>--%>
						<%--			<option value="图书馆">图书馆</option>--%>
						<%--			<option value="档案中心">档案中心</option>--%>
						<%--		</select></td>--%>
						<%--	<td class="validate-tips" colspan="3" id='msg11'>--%>
						<%--		选填。--%>
						<%--	</td>--%>
						<%--</tr>--%>
						<tr>
							<th width="295">&nbsp;</th>
							<th width="106"><span class="required">*</span>通讯地址</th>
							<td colspan="2">
								<input type="text" name="address" id="address" value="" class="smzc-input" placeholder="请填写您的通讯地址" autocomplete="off"/>
							</td>
							<%--<td class="validate-tips" colspan="3" id='msg12'>--%>
							<%--	请如实填写。--%>
							<%--</td>--%>
						</tr>
						<tr>
							<th width="295">&nbsp;</th>
							<th width="106"><span class="required"></span>办公电话</th>
							<td colspan="2">
								<input type="text" name="officePhone" id="officePhone" value="" class="smzc-input" placeholder="请填写您的办公电话" autocomplete="off"/>
							</td>
							<%--<td class="validate-tips" colspan="3" id='msg13'>--%>
							<%--	选填。--%>
							<%--</td>--%>
						</tr>
						<tr>
							<th width="295">&nbsp;</th>
							<th width="106"><span class="required">*</span>家庭电话</th>
							<td colspan="2">
								<input type="text" name="homePhone" id="homePhone" value="" class="smzc-input" placeholder="请填写您的家庭电话" autocomplete="off"/>
							</td>
							<%--<td class="validate-tips" colspan="3" id='msg14'>--%>
							<%--	此信息作为联系方式，请填务必如实填写。--%>
							<%--</td>--%>
						</tr>
						<tr>
							<th width="295">&nbsp;</th>
							<th><span class="required">*</span>电子邮箱</th>
							<td colspan="2">
								<input type="text" name="email" value="" id="email" class="smzc-input" placeholder="请填写您的电子邮箱" autocomplete="off"/>
							<%--	onBlur="checkEmail()" --%>
							</td>
							<%--<td class="validate-tips" colspan="3" id='email-msg'>--%>
							<%--	请设定一个安全邮箱，忘记密码时可通过此邮箱找回密码。--%>
							<%--</td>--%>
						</tr>
						<tr>
							<th width="295">&nbsp;</th>
							<th><span class="required">*</span>工号/学号</th>
							<td colspan="2">
								<input type="text" name="username" id="username" value="" class="smzc-input" placeholder="请填写您的工号或学号" autocomplete="off" tip="工资号不能为空！" usage="notempty"/>
							</td>
							<%--<td class="validate-tips" colspan="3" id='msg8'>--%>
							<%--	该项必填！作为登录账号使用。工资号为学校分配，请确认后填写。--%>
							<%--</td>--%>
						</tr>
						<tr>
							<th width="295">&nbsp;</th>
							<th><span class="required">*</span>密码</th>
							<td colspan="2">
								<input type="password" name="password" id="password" class="smzc-input" placeholder="请填写您的密码" tip="密码不能为空！" usage="notempty"/>
							</td>

						</tr>
						<tr>
							<th width="295">&nbsp;</th>
							<th><span class="required">*</span>确认密码</th>
							<td colspan="2">
								<input type="password" name="password1" id="password1" class="smzc-input" placeholder="请再次填写您的密码" tip="密码不能为空！" usage="notempty"/>
							</td>

						</tr>
						<tr>
							<th width="295">&nbsp;</th>
							<th class='wap-hide'>&nbsp;</th>
							<td colspan="5">
								<input type="submit" id="newbutton" name="newbutton" value='立即注册' class="smzc-input"/>
							</td>
						</tr>
						<tr>
							<th width="295">&nbsp;</th>
							<th class='wap-hide'>&nbsp;</th>
							<td colspan="5">
								<input type="reset" id="Reset" name="Reset" value='重置' class="smzc-input"/>
							</td>
						</tr>
					</table>
				</form>
			</div>
		</div>
		<%--<script src="https://t4.chei.com.cn/account/js/account/vcodetimehold-1.0.0.js"></script>--%>
		<%--<script src='https://t1.chei.com.cn/account/js/jquery/jquery.pstrength-chsi-2.3.js'></script>--%>
		<%--<script src='https://t3.chei.com.cn/account/js/automail.js'></script>--%>
		<%--<script src='https://t4.chei.com.cn/account/js/account/reg/account-sfzh-1.0.1.js'></script>--%>
		<%--<script src='https://t4.chei.com.cn/account/js/account/registerbysfzh-2.0.14.js'></script>--%>
		<%--<script src='https://t1.chei.com.cn/common/js/poshytip/jquery.poshytip.min.js'></script>--%>
		<%--<script>--%>
        <%--    var optionText = $("#optionText").text();--%>
        <%--    $(function () {--%>
        <%--        clickFn();--%>
        <%--        $("#password").pstrength();//密码校验强度--%>
        <%--        $('#email').autoMail().attr('placeholder', optionText);//邮箱自动完成--%>

        <%--        //默认密码强度条隐藏--%>
        <%--        $(".strengthMeter").hide();--%>
        <%--        $("#password").keyup(function(){--%>
        <%--            if($("#password").val() != ""){--%>
        <%--                $(".strengthMeter").show();--%>
        <%--            }else{--%>
        <%--                $(".strengthMeter").hide();--%>
        <%--            }--%>
        <%--        });--%>

        <%--        if (wapFn()) {--%>
        <%--            $(".regist-tips-box").insertAfter("#user_reg_fm");--%>
        <%--            //折叠效果--%>
        <%--            $(".toggle-icon-wap").click(function() {--%>
        <%--                var $this = $(this);--%>
        <%--                if ($this.attr("data-flag") === "1") {--%>
        <%--                    $this.html("&#xe602;").siblings(".regist-tip-detail").show();--%>
        <%--                    $this.siblings("h2").css({--%>
        <%--                        "white-space": "normal",--%>
        <%--                        "width": "auto"--%>
        <%--                    });--%>
        <%--                    $this.attr("data-flag", "0");--%>
        <%--                } else {--%>
        <%--                    $this.html("&#xe600;").siblings(".regist-tip-detail").hide();--%>
        <%--                    $this.siblings("h2").css({--%>
        <%--                        "white-space": "nowrap",--%>
        <%--                        "width": "90%"--%>
        <%--                    });--%>
        <%--                    $this.attr("data-flag", "1");--%>
        <%--                }--%>
        <%--            });--%>
        <%--        }--%>
        <%--    });--%>
		<%--</script>--%>
	</div>
</div>
</body>
</html>
