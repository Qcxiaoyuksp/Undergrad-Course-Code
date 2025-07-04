<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%
	String basePath = request.getScheme() + "://" + request.getServerName() + ":" + request.getServerPort()
		+ request.getContextPath() + "/";
%>
<!DOCTYPE HTML>
<html>
<head>
	<title>论文管理系统</title>
	<jsp:include page="../common/css.jsp"></jsp:include>
	<style>
		body {
			background-image: url("static/images/01.jpg");
		}
	</style>
</head>
<body class="bootstrap-admin-with-small-navbar">
	<jsp:include page="../common/top.jsp"></jsp:include>

	<div class="container">
			<jsp:include page="../common/left.jsp"></jsp:include>
			
			<!-- content -->
			<div class="col-md-10">
				<div class="row">
					<div class="col-lg-12">
						<div class="panel panel-default bootstrap-admin-no-table-panel">
							<div class="panel-heading">
								<div class="text-muted bootstrap-admin-box-title">论文管理</div>
							</div>
							<div
								class="bootstrap-admin-no-table-panel-content bootstrap-admin-panel-content collapse in">
								<form class="form-horizontal" action="/books_MA/selectServlet"
									method="post">
									<div class="col-lg-3 form-group">
										<button type="button" class="btn btn-primary" id="btn_add" 
											data-toggle="modal" data-target="#addModal">添加用户</button>
									</div>
								</form>
							</div>
						</div>
					</div>
				</div>

				<div class="row">
					<div class="col-lg-12">
						<table id="data_list" class="table table-hover table-bordered"
							cellspacing="0" width="100%">
							<thead>
								<tr>
									<th>ID</th>
									<th>账号</th>
									<th>姓名</th>
									<th>手机号</th>
									<th>家庭住址</th>
									<th>毕业学校</th>
									<th>年龄</th>
									<th>电子邮箱</th>
									<th>操作</th>
								</tr>
							</thead>

							<tbody>
								<c:forEach items="${uList}" var="user" varStatus="status">
									<tr>
										<td>${user.uid}</td>
										<td>${user.account}</td>
										<td>${user.name}</td>
										<td>${user.phone}</td>
										<td>${user.address}</td>
										<td>${user.graduate}</td>
										<td>${user.age}</td>
										<td>${user.email}</td>
										<td><button type="button" class="btn btn-warning btn-xs btn-block"
										data-toggle="modal" data-target="#updateModal" id="btn_update"
										onclick="showInfo2('${user.uid}','${user.account}','${user.name}',
										'${user.phone}','${user.address}','${user.graduate}','${user.age}','${user.email}')">修改</button>
									<button type="button" class="btn btn-danger btn-xs btn-block"
										onclick="deleteUser(${user.uid})">删除</button></td>
									</tr>
								</c:forEach>
							</tbody>
						</table>
						${requestScope.pagation}
					</div>
				</div>
			</div>
		</div>
	
	<script type="text/javascript">
    function showInfo2(uid,account,name,phone,lend_num,max_num,address,graduate,age,email) {
        document.getElementById("updateusername").value = account;
        document.getElementById("updatename").value = name;
        document.getElementById("updatephone").value = phone;
        document.getElementById("updateaid").value = uid;
        document.getElementById("updateaddress").value = address;
        document.getElementById("updategraduate").value = graduate;
        document.getElementById("updateage").value = age;
        document.getElementById("updateemail").value =email;
        
    }
    function deleteUser(uid) {
    	con=confirm("是否删除?"); 
    	if(con==true){
    		location.href = "/books_MA/user?method=delUser&uid="+uid;
    	}
    }
    </script>
	<!-- 修改模态框（Modal） -->
	<!-------------------------------------------------------------->
	
	<!-- 修改模态框（Modal） -->
	<form class="form-horizontal" method="post" 
		action="/books_MA/user?method=updUser">
		<!--保证样式水平不混乱-->
		<div class="modal fade" id="updateModal" tabindex="-1" role="dialog"
			aria-labelledby="updateModalLabel" aria-hidden="true">
			<div class="modal-dialog">
				<div class="modal-content">
					<div class="modal-header">
						<button type="button" class="close" data-dismiss="modal"
							aria-hidden="true">&times;</button>
						<h4 class="modal-title" id="updateModalLabel">修改读者信息</h4>
					</div>
					<div class="modal-body">

						<!---------------------表单-------------------->

						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">账号</label>
							<div class="col-sm-7">
								<input type="hidden" id="updateaid" name="uid"> 
								<input
									type="text" class="form-control" id="updateusername"
									name="account" placeholder="" readonly="readonly"> <label
									class="control-label" for="updateISBN" style="display: none;"></label>
							</div>
						</div>
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">姓名</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="updatename"
									name="name" placeholder="" readonly="readonly"> <label
									class="control-label" for="updateBookName"
									style="display: none;"></label>
							</div>
						</div>
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">手机号</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="updatephone"
									name="phone" placeholder=""> <label
									class="control-label" for="updatePress" style="display: none;"></label>
							</div>
						</div>
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">家庭地址</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="updateaddress"
									name="updateaddress" placeholder=""> <label
									class="control-label" for="updatePress" style="display: none;"></label>
							</div>
						</div>
						
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">毕业学校</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="updategraduate"
									name="updategraduate" placeholder=""> <label
									class="control-label" for="updatePress" style="display: none;"></label>
							</div>
						</div>
						
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">年龄</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="updateage"
									name="updateage" placeholder=""> <label
									class="control-label" for="updatePress" style="display: none;"></label>
							</div>
						</div>
						
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">电子邮箱</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="updateemail"
									name="updateemail" placeholder=""> <label
									class="control-label" for="updatePress" style="display: none;"></label>
							</div>
						</div>
						
					</div>
					<div class="modal-footer">
						<button type="button" class="btn btn-default"
							data-dismiss="modal">关闭</button>
						<button type="submit" class="btn btn-primary ">修改</button>
					</div>
				</div>
				<!-- /.modal-content -->
			</div>
			<!-- /.modal -->
		</div>
	</form>

	<!-------------------------------------------------------------->

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
						<!--<h4 class="modal-title" id="myModalLabel">添加新读者</h4>  -->
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
								<label class="control-label" for="addaddress"
									style="display: none;"></label>
							</div>
						</div>
						
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">毕业学校</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" name="graduate"
									id="addgraduate" required="required" placeholder="请输入毕业学校">
								<label class="control-label" for="addgraduate"
									style="display: none;"></label>
							</div>
						</div>
						
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">年龄</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" name="age"
									id="addage" required="required" placeholder="请输入年龄">
								<label class="control-label" for="addage"
									style="display: none;"></label>
							</div>
						</div>
						
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">电子邮箱</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" name="email"
									id="addemail" required="required" placeholder="请输入电子邮箱">
								<label class="control-label" for="addemail"
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
	<!--------------------------------------添加的模糊框------------------------>

	<jsp:include page="../common/userInfo.jsp"></jsp:include>
	<jsp:include page="../common/js.jsp"></jsp:include>
	<script type="text/javascript">
	var f=false;
	 $("#addISBN").blur(function(){
		 $.get("${pageContext.request.contextPath}/user?method=checkUser",{"account":$("#addISBN").val()},function(res){
			//json字符串转换对象
			var obj=JSON.parse(res);
			 if(obj.code==200){
				//账号可以被使用
				
				$("#msg").css({"color":"green"});
				$("#addISBN").css({"border-color":"green"});
				f=true;
			 }else{
				 $("#msg").css({"color":"red"});
					$("#addISBN").css({"border-color":"red"});
				 f=false;
			 }
			 $("#msg").html(obj.msg);
		 });
	 });
	 function checkAdd(){
		 return f;
	 }
	 </script>
	
</body>
</html>