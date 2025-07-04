<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<!DOCTYPE HTML>
<html class="ax-vertical-centered">
<head>
	<title>图书借阅信息</title>
	<jsp:include page="../common/css.jsp"></jsp:include>
	<script src="static/js/bootstrap.min.js"></script>
	<script src="static/jQuery/jquery-3.1.1.min.js"></script>
	<script src="static/js/bootstrap-dropdown.min.js"></script>
	<script src="static/js/adminUpdateInfo.js"></script>
	<script src="static/js/adminUpdatePwd.js"></script>
	<style>
		body {
			background-image: url("static/images/01.jpg");
		}
	</style>
</head>

<script src="static/js/jquery.min.js"></script>
<script src="static/js/bootstrap.min.js"></script>

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
								<div class="text-muted bootstrap-admin-box-title">图书借阅信息</div>
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
									<th>序号</th>
									<th>图书名称</th>
									<th>读者账号</th>
									<th>读者姓名</th>
									<th>借阅日期</th>
									<th>截止还书日期</th>
									<th>操作</th>
								</tr>
							</thead>
							<tbody>
								<c:forEach items="${hList}" var="history" varStatus="status">
									<tr>
<%-- 										<td>${history.card}</td> --%>
										<td>${status.index+1}</td>
										<td>${history.bookName}</td>
										<td>${history.account}</td>
										<td>${history.name}</td>
										<td>
											<fmt:formatDate value="${history.beginTime}" pattern="yyyy-MM-dd HH:mm:ss"/>					
										</td>
										<td>
											<fmt:formatDate value="${history.endTime}" pattern="yyyy-MM-dd HH:mm:ss"/>															
										</td>
										<td><button type="button" class="btn btn-warning btn-xs"
										onclick="haibook(${history.hid})">还书</button>
									<button type="button" class="btn btn-info btn-xs"
										data-toggle="modal" data-target="#updateModal" id="btn_add"
										onclick="addtime('${history.hid}','${history.endTime}')">延期</button></td>
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
    function haibook(hid) {
    	con=confirm("是否还书?"); 
    	if(con==true){
    		location.href = "/books/book?method=borrow&tip=2&show=2&hid="+hid;
    	}
    }
    function addtime(hid,endtime){
    	document.getElementById("updatehid").value = hid;
    	document.getElementById("updateendtime").value = endtime;
    }
    </script>
    <!-- 修改模态框（Modal） -->
	<!-------------------------------------------------------------->
	
    <!-- 修改模态框（Modal） -->
	<form class="form-horizontal" method="post"
		action="/books/book?method=addTime">
		<!--保证样式水平不混乱-->
		<div class="modal fade" id="updateModal" tabindex="-1" role="dialog"
			aria-labelledby="updateModalLabel" aria-hidden="true">
			<div class="modal-dialog">
				<div class="modal-content">
					<div class="modal-header">
						<button type="button" class="close" data-dismiss="modal"
							aria-hidden="true">&times;</button>
						<h4 class="modal-title" id="updateModalLabel">延长借阅时间</h4>
					</div>
					<div class="modal-body">

						<!---------------------表单-------------------->

						<div class="form-group">
							<label for="endtime" class="col-sm-3 control-label">截至还书时间</label>
							<div class="col-sm-7">
								<input type="hidden" id="updatehid" name="hid">
								<input type="text" class="form-control" id="updateendtime"
									name="endtime" placeholder=""> <label
									class="control-label" for="updateTime" style="display: none;"></label>
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

	<!--------------------------------------修改密码的模糊框------------------------>

	<jsp:include page="../common/userInfo.jsp"></jsp:include>
	<jsp:include page="../common/userInfo.jsp"></jsp:include>
</body>
</html>