<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<!DOCTYPE HTML>
<html class="ax-vertical-centered">
<head>
<meta charset="UTF-8">
	<title>图书馆管理系统</title>
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
		<!-- left, vertical navbar & content -->
		<div class="row">
			<jsp:include page="../common/user_left.jsp"></jsp:include>
			
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
								<form class="form-horizontal" action="/books/brtimesServlet"
									method="post">
									<input type="hidden" name="tip" value="2">
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

							<!---在此插入信息-->
							<%-- <%
								ArrayList<AdminBean> data2 = new ArrayList<AdminBean>();
								data2 = (ArrayList<AdminBean>) request.getAttribute("data");
								if (data2 == null) {
									data2 = (ArrayList<AdminBean>) admindao.get_ListInfo3();
								}
								for (AdminBean bean : data2) {
							%>
							<tbody>
								<td><%=bean.getTimes()%></td>
								<td><%=bean.getAid()%></td>
								<td><%=bean.getName()%></td>
								<td><%=bean.getUsername()%></td>
							</tbody>
							<%
								}
							%> --%>
						</table>
					</div>
				</div>
			</div>
		</div>
	</div>
	<!--------------------------------------添加的模糊框------------------------>

	<!-------------------------------------------------------------->

	<jsp:include page="../common/userInfo.jsp"></jsp:include>
	<jsp:include page="../common/js.jsp"></jsp:include>
</body>
</html>