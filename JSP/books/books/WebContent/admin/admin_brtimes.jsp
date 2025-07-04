<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE HTML>
<html class="ax-vertical-centered">
<head>
	<title>用户排行</title>
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
		<div class="row">
			<jsp:include page="../common/left.jsp"></jsp:include>
			
			<!-- content -->
			<div class="col-md-10">
				<div class="row">
					<div class="col-lg-12">
						<div class="panel panel-default bootstrap-admin-no-table-panel">
							<div class="panel-heading">
								<div class="text-muted bootstrap-admin-box-title">读者借书量查询</div>
							</div>
							<div
								class="bootstrap-admin-no-table-panel-content bootstrap-admin-panel-content collapse in">
								<form class="form-horizontal" action="/books/user?method=rankLike"
									method="post">
									<input type="hidden" name="tip" value="1">
									<div class="col-lg-8 form-group">
										<label class="col-lg-4 control-label" for="query_bname">读者信息</label>
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
									<th>借阅量</th>
									<th>ID</th>
									<th>姓名</th>
									<th>账号</th>
								</tr>
							</thead>
							<tbody>
								<c:forEach items="${rList}" var="user" varStatus="status">
									<tr>
										<td>${user.times}</td>
										<td>${user.uid}</td>
										<td>${user.name}</td>
										<td>${user.account}</td>
									</tr>
								</c:forEach>
							</tbody>
						</table>
					</div>
				</div>
			</div>
		</div>
	</div>
	<!--------------------------------------添加的模糊框------------------------>

	<jsp:include page="../common/userInfo.jsp"></jsp:include>
	<jsp:include page="../common/js.jsp"></jsp:include>
</body>
</html>