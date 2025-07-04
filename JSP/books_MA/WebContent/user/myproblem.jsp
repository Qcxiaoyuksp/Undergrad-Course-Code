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
								<div class="text-muted bootstrap-admin-box-title">我的反馈</div>
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
									<th>标题</th>
									<th>问题页面</th>
									<th>问题描述</th>
									<th>联系方式</th>
									<th>问题状态</th>
								</tr>
							</thead>

							<!---在此插入信息-->
							<%-- <%
							ArrayList<ProblemBean> data2 = new ArrayList<ProblemBean>();
							data2 = (ArrayList<ProblemBean>) request.getAttribute("data");
							if (data2 == null) {
								ProblemDao problemdao = new ProblemDao();
								data2 = (ArrayList<ProblemBean>) problemdao.get_ListInfo2(aid);
							}

							for (ProblemBean bean : data2) {
							%>
							<tbody>
								<td><%=bean.getPid()%></td>
								<td><%=bean.getName()%></td>
								<td><%=bean.getPage()%></td>
								<td><%=bean.getBody()%></td>
								<td><%=bean.getPhone()%></td>
								<td><%=bean.getStatus()%></td>
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

	<jsp:include page="../common/userInfo.jsp"></jsp:include>
	<jsp:include page="../common/js.jsp"></jsp:include>
</body>
</html>