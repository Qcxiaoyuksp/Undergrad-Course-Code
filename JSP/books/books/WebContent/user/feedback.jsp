<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<!DOCTYPE HTML>
<html class="ax-vertical-centered">
<head>
	<title>图书馆管理系统</title>
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
			<jsp:include page="../common/user_left.jsp"></jsp:include>
			<!-- content -->
			<div class="col-md-10">
				<div class="row">
					<div class="col-lg-12">
						<div class="panel panel-default bootstrap-admin-no-table-panel">
							<div class="panel-heading">
								<div class="text-muted bootstrap-admin-box-title">问题反馈</div>
							</div>
							<div
								class="bootstrap-admin-no-table-panel-content bootstrap-admin-panel-content collapse in">
								<form class="form-horizontal" action="/books/AddProblemServlet"
									method="post">
									<div class="col-lg-8 form-group">
										<label class="col-lg-4" for="query_bname">标题</label>
										<div class="col-lg-12">
											<input class="form-control" id="bookName" name="name"
												type="text" value="" required="required" placeholder="请勿超过30个字符">
											<label for="query_bname" style="display: none;"></label>
										</div>
									</div>
									<div class="col-lg-8 form-group">
										<label class="col-lg-4" for="query_bname">问题页面</label>
										<div class="col-lg-12">
											<input class="form-control" id="bookName" name="page"
												type="text" value="" required="required" placeholder="books/XXX.jsp(仅填写XXX处)">
											<label for="query_bname" style="display: none;"></label>
										</div>
									</div>
									<div class="col-lg-8 form-group">
										<label class="col-lg-4" for="query_bname">问题描述</label>
										<div class="col-lg-12">
											<textarea name="body" required="required" class="form-control" placeholder="请勿超过255个字符"
												style="height: 150px;resize: none;"></textarea>
											<label for="query_bname" style="display: none;"></label>
										</div>
									</div>
									<div class="col-lg-8 form-group">
										<label class="col-lg-4" for="query_bname">联系方式</label>
										<div class="col-lg-12">
											<input class="form-control" id="bookName" name="phone"
												type="text" value="" required="required" placeholder="电话/邮箱">
											<label for="query_bname" style="display: none;"></label>
										</div>
									</div>
									<div class="col-lg-8 form-group">
										<label class="control-label" for="query_bname"></label>
										<button type="submit" class="btn btn-primary" id="btn_query">提 交</button>
										<label for="query_bname" style="display: none;"></label>&nbsp;
										<a href="/books/myproblem.jsp"><i
											class="glyphicon glyphicon-chevron-right"></i> 我的反馈</a>
									</div>
								</form>
							</div>
						</div>
					</div>
				</div>
			</div>
		</div>
	</div>

	<!-------------------------------------------------------------->

	<jsp:include page="../common/userInfo.jsp"></jsp:include>
	<jsp:include page="../common/js.jsp"></jsp:include>
</body>
</html>