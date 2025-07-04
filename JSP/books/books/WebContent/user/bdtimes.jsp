<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<!DOCTYPE HTML>
<html class="ax-vertical-centered">
<head>
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
								<div class="text-muted bootstrap-admin-box-title">借阅次数查询</div>
							</div>
							<div
								class="bootstrap-admin-no-table-panel-content bootstrap-admin-panel-content collapse in">
								<form class="form-horizontal" action="/books/bdtimesServlet"
									method="post">
									<input type="hidden" name="tip" value="2">
									<div class="col-lg-8 form-group">
										<label class="col-lg-4 control-label" for="query_bname">图书信息</label>
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
									<th>借阅次数</th>
									<th>图书号</th>
									<th>图书类型</th>
									<th>图书名称</th>
									<th>作者名称</th>
									<th>出版社</th>
									<th>总数量</th>
									<th>操作</th>
								</tr>
							</thead>

							<!---在此插入信息-->
							<!---在此插入信息-->
							<%-- <%
								ArrayList<BookBean> bookdata = new ArrayList<BookBean>();
								bookdata = (ArrayList<BookBean>) request.getAttribute("data");
								if (bookdata == null) {
									BookDao bookdao = new BookDao();
									bookdata = (ArrayList<BookBean>) bookdao.get_ListInfo2();
								}
	
								for (BookBean bean : bookdata) {
							%>
							<tbody>
								<td><%=bean.getTimes()%></td>
								<td><%=bean.getCard()%></td>
								<td><%=bean.getType()%></td>
								<td><%=bean.getName()%></td>
								<td><%=bean.getAutho()%></td>
								<td><%=bean.getPress()%></td>
								<td><%=bean.getNum()%></td>
								<td><button type="button" class="btn btn-info btn-xs"
										data-toggle="modal" onclick="borrowbook(<%=bean.getBid()%>)">借阅</button>
								</td>
							</tbody>
							<%
								}
							%> --%>
						</table>
					</div>
				</div>
				<script type="text/javascript">
			    function borrowbook(bid) {
			    	con=confirm("是否借阅?"); 
			    	if(con==true){
			    		location.href = "/books/borrowServlet?tip=1&show=2&bid="+bid;
			    	}
			    }
			    </script>
			</div>
		</div>
	</div>

	<!-------------------------------------------------------------->

	<jsp:include page="../common/userInfo.jsp"></jsp:include>
	<jsp:include page="../common/js.jsp"></jsp:include>
</body>
</html>