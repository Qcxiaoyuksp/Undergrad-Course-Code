<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE HTML>
<html class="ax-vertical-centered">
<head>
	<title>图书馆管理系统</title>
	<jsp:include page="../common/css.jsp"></jsp:include>
	<style>
		body {
			background-image: url("static/images/03.jpg");
		}
	</style>
</head>

<body class="bootstrap-admin-with-small-navbar">
	<jsp:include page="../common/top.jsp"></jsp:include>

	<div class="container">
			<jsp:include page="../common/user_left.jsp"></jsp:include>

			<!-- content -->
			<div class="col-md-10">
				<div class="row">
					<div class="col-lg-12">
						<div class="panel panel-default bootstrap-admin-no-table-panel">
							<div class="panel-heading">
								<div class="text-muted bootstrap-admin-box-title">借阅记录</div>
							</div>
						</div>
					</div>
				</div>
				<div class="row">
					<div class="col-lg-12"></div>
				</div>
				<div class="row">
					<div class="col-lg-12">
						<table id="data_list" class="table table-hover table-bordered"
							cellspacing="0" width="100%">
							<thead>
								<tr>
									<th>图书名称</th>
									<th>读者账号</th>
									<th>读者姓名</th>
									<th>借阅日期</th>
									<th>还书日期</th>
								</tr>
							</thead>
							<tbody>
								<c:forEach items="${hList}" var="history" varStatus="status">
									<tr>
										<td>${history.bookName}</td>
										<td>${history.account}</td>
										<td>${history.name}</td>
										<td>${history.beginTime}</td>
										<td>${history.endTime}</td>
									</tr>								
								</c:forEach>
							</tbody>
						</table>
					</div>
				</div>
			</div>
		</div>
	<!-------------------------------------------------------------->

	<jsp:include page="../common/userInfo.jsp"></jsp:include>
	<jsp:include page="../common/js.jsp"></jsp:include>
</body>
</html>