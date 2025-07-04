<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%
	String basePath = request.getScheme() + "://" + request.getServerName() + ":" + request.getServerPort()
		+ request.getContextPath() + "/";
%>
<!DOCTYPE HTML>
<html>
<head>
	<base href="<%=basePath%>" />
	<title>论文管理系统</title>
	<jsp:include page="common/css.jsp"></jsp:include>
	<style>
		body {
			background-image: url("static/images/02.jpg");
		}
		.alert {
			margin: 0 auto 20px;
			text-align: center;
		}
	</style>
</head>

<body class="bootstrap-admin-without-padding">
	<div class="container">
		<div class="row">
			<div class="col-lg-12" style="margin-top: 100px">
				<div class="alert alert-info">
					<a class="close" data-dismiss="alert" href="#">&times;</a>
					欢迎登录论文管理系统
				</div>
				<form class="bootstrap-admin-login-form" method="post"
					action="<%=basePath%>login?method=login">
					<%
						String state = (String) session.getAttribute("state");
						session.removeAttribute("state");
						if (state != null) {
					%>
					<label class="control-label" for="username">输入有误！请重试</label>

					<%}%>
					<div class="form-group">
						<label class="control-label" for="username">账&nbsp;号</label> <input
							type="text" class="form-control" id="username" name="account"
							required="required" placeholder="请输入账号" /> <label
							class="control-label" for="username" style="display: none;"></label>
					</div>
					<div class="form-group">
						<label class="control-label" for="password">密&nbsp;码</label> <input
							type="password" class="form-control" id="password"
							name="password" required="required" placeholder="请输入密码" /> <label
							class="control-label" for="username" style="display: none;"></label>
					</div>

					<label class="control-label" for="password">没有账号请联系管理员<a
						href="/books_MA/register.jsp" style="color: blue;">注册</a></label> 
						
						<br> 
						
						<div>
						  <button type="button" class="btn btn-primary btn-block" id="btn_add" 
								data-toggle="modal" data-target="#addModal">注册
						  </button>
						</div>
						
						
						<br> <input
						type="submit" class="btn btn-lg btn-primary btn-block"
						value="登&nbsp;&nbsp;&nbsp;&nbsp;录" />
				</form>
			</div>
		</div>
	</div>
	
	
	<!--------------------------------------添加的模糊框------------------------>
	<form class="form-horizontal" method="post" onsubmit = "return checkAdd() "
		action="/books_MA/user?method=addUser">
		<!--保证样式水平不混乱-->
		<!-- 模态框（Modal） -->
		<div class="modal fade" id="addModal" tabindex="-1" role="dialog"
			aria-labelledby="myModalLabel" aria-hidden="true">
			<div class="modal-dialog">
				<div class="modal-content">
					<div class="modal-header">
						<button type="button" class="close" data-dismiss="modal"
							aria-hidden="true">&times;</button>
						<!--<h4 class="modal-title" id="myModalLabel">添加新用户</h4>  -->
						<h5 style="text-align:center" id="msg"></h5>
					</div>
					<div class="modal-body">

						<!---------------------表单-------------------->

						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">账号</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" name="account"
									id="addISBN" required="required" placeholder="请输入账号">
								<label class="control-label" for="addISBN"
									style="display: none;"></label>
							</div>
						</div>

						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">姓名</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" name="name"
									id="addBookName" required="required" placeholder="请输入姓名">
								<label class="control-label" for="addBookName"
									style="display: none;"></label>
							</div>
						</div>


						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">手机号</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" name="phone"
									id="addPress" required="required" placeholder="请输入手机号">
								<label class="control-label" for="addPress"
									style="display: none;"></label>								</div>
							</div>
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">密码</label>
							<div class="col-sm-7">
								<input type="password" class="form-control" name="password"
									id="addPress" required="required" placeholder="请输入密码">
								<label class="control-label" for="addPress"
									style="display: none;"></label>
							</div>
						</div>
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">用户角色</label>
							<div class="col-sm-7">
								<select class="form-control" id="addBookType" name="role">
										<option value="1">普通用户</option>
										<option value="2">管理员</option>
								</select> 
								<label class="control-label" for="addBookType"
									style="display: none;"></label>
							</div>
						</div>
						
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">家庭地址</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" name="address"
									id="addaddress" required="required" placeholder="请输入家庭地址">
								<label class="control-label" for="addAddress"
									style="display: none;"></label>
							</div>
						</div>
						
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">毕业学校</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" name="graduate"
									id="addgraduate" required="required" placeholder="请输入毕业学校">
								<label class="control-label" for="addGraduate"
									style="display: none;"></label>
							</div>
						</div>
						
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">年龄</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" name="age"
									id="addage" required="required" placeholder="请输入年龄">
								<label class="control-label" for="addAge"
									style="display: none;"></label>
							</div>
						</div>
						
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">电子邮箱</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" name="email"
									id="addemail" required="required" placeholder="请输入电子邮箱">
								<label class="control-label" for="addEmail"
									style="display: none;"></label>
							</div>
						</div>
						
						
						
					</div>
					<div class="modal-footer">
						<button type="button" class="btn btn-default"
							data-dismiss="modal">关闭</button>
						<button type="submit" class="btn btn-primary">添加</button>
					</div>
				</div>
				<!-- /.modal-content -->
			</div>
			<!-- /.modal -->
		</div>
	</form>
	
	<script src="static/jQuery/jquery-3.1.1.min.js"></script>
	<script src="static/js/bootstrap.min.js"></script>
	<script src="static/js/login.js"></script>
	<script type="text/javascript">
		function changeValidateCode(obj) {
			//每次请求用当前时间作为参数，防止浏览器使用缓存数据
			var timeNow = new Date().getTime();
			obj.src = "CodeServlet?time=" + timeNow;
			document.getElementById('code').value = "";
		}
	</script>
	
	
	<jsp:include page="/common/userInfo.jsp"></jsp:include>
	<jsp:include page="/common/js.jsp"></jsp:include>
	<script type="text/javascript">
	 $("#addISBN").blur(function(){
		 $.get("${pageContext.request.contextPath}/user?method=checkUser",{"account":$("#addISBN").val()},function(res){
			alert(res);
		 });
	 });
	 </script>
</body>
</html>