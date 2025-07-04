<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE HTML>
<html class="ax-vertical-centered">
<head>
	<title>用户反馈</title>
	<jsp:include page="../common/css.jsp"></jsp:include>
	<style>
	body {
		background-image: url("04.jpg");
	}
	</style>
</head>

<body class="bootstrap-admin-with-small-navbar">
	<jsp:include page="../common/top.jsp"></jsp:include>
	<div class="container">
		<!-- left, vertical navbar & content -->
		<div class="row">
			<jsp:include page="../common/left.jsp"></jsp:include>

			<!-- content -->
			<div class="col-md-10">
				<div class="row">
					<div class="col-lg-12">
						<div class="panel panel-default bootstrap-admin-no-table-panel">
							<div class="panel-heading">
								<div class="text-muted bootstrap-admin-box-title">读者反馈查询</div>
							</div>
							<div
								class="bootstrap-admin-no-table-panel-content bootstrap-admin-panel-content collapse in">
								<form class="form-horizontal" action="/books/problem?method=list"
									method="post">
									<div class="col-lg-8 form-group">
										<label class="col-lg-4 control-label" for="query_bname">反馈信息</label>
										<div class="col-lg-8">
											<input class="form-control" id="bookName" name="name"
												type="text" value=""> <label class="control-label"
												for="query_bname" style="display: none;"></label>
										</div>
									</div>
									<div class="col-lg-4 form-group">
										<button type="submit" class="btn btn-primary" id="btn_query">查询</button>
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
									<th>读者ID</th>
									<th>标题</th>
									<th>问题页面</th>
									<th>问题描述</th>
									<th>联系电话</th>
									<th>问题状态</th>
									<th>操作</th>
								</tr>
							</thead>
							<tbody>
								<c:forEach items="${pList}" var="problem" varStatus="status">
									<tr>
										<td>${problem.pid}</td>
										<td>${problem.aid}</td>
										<td>${problem.name}</td>
										<td>${problem.page}</td>
										<td>${problem.body}</td>
										<td>${problem.phone}</td>
										<td>${problem.status}</td>
										<td><button type="button" class="btn btn-warning btn-xs"
										data-toggle="modal" data-target="#updateModal" id="btn_update"
										onclick="showInfo2('${problem.pid}','${problem.status}')">修改</button>
									<button type="button" class="btn btn-danger btn-xs"
										onclick="deleteproblem(${problem.pid})">删除</button></td>
									</tr>
								</c:forEach>
							</tbody>
						</table>
					</div>
				</div>
				<script type="text/javascript">
				function showInfo2(pid,status) {
			        document.getElementById("updatepid").value = pid;
			        document.getElementById("updatestatus").value = status;
			    }
			    function deleteproblem(pid) {
			    	con=confirm("是否删除?"); 
			    	if(con==true){
			    		location.href = "/books/problem?method=delete&pid="+pid;
			    	}
			    }
			    </script>
			</div>
		</div>
	</div>
	<!-- 修改模态框（Modal） -->
	<!-------------------------------------------------------------->
	
	<!-- 修改模态框（Modal） -->
	<form class="form-horizontal" method="post"
		action="/books/problem?method=update">
		<!--保证样式水平不混乱-->
		<div class="modal fade" id="updateModal" tabindex="-1" role="dialog"
			aria-labelledby="updateModalLabel" aria-hidden="true">
			<div class="modal-dialog">
				<div class="modal-content">
					<div class="modal-header">
						<button type="button" class="close" data-dismiss="modal"
							aria-hidden="true">&times;</button>
						<h4 class="modal-title" id="updateModalLabel">修改反馈状态</h4>
					</div>
					<div class="modal-body">

						<!---------------------表单-------------------->

						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">状态</label>
							<div class="col-sm-7">
								<input type="hidden" name="pid" id="updatepid"> <input 
									type="text" class="form-control" id="updatestatus"
									name="status" placeholder=""> <label
									class="control-label" for="updateISBN" style="display: none;"></label>
							</div>
						</div>
					<div class="modal-footer">
						<button type="button" class="btn btn-default"
							data-dismiss="modal">关闭</button>
						<button type="submit" class="btn btn-primary">修改</button>
					</div>
				</div>
				<!-- /.modal-content -->
			</div>
			<!-- /.modal -->
		</div>
	</form>

	<jsp:include page="../common/userInfo.jsp"></jsp:include>
	<jsp:include page="../common/js.jsp"></jsp:include>
</body>
</html>