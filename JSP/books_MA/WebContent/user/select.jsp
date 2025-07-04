<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE HTML>
<html class="ax-vertical-centered">
<head>
	<title>论文管理系统</title>
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
								<div class="text-muted bootstrap-admin-box-title">查询</div>
							</div>
							<div
								class="bootstrap-admin-no-table-panel-content bootstrap-admin-panel-content collapse in">
								<form class="form-horizontal" action="/books_MA/book?method=listByPage"
									method="post">
									<input type="hidden" name="tip" value="2">
									<div class="col-lg-8 form-group">
										<label class="col-lg-4 control-label" for="query_bname">论文信息</label>
										<div class="col-lg-8">
											<input class="form-control" id="bookName" name="word"
												type="text" value="${word}"> <label class="control-label"
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
								  <th>序号</th>
									<th>论文类型</th>
									<th>论文名称</th>
									<th>论文名称</th>
									<th>论文认证</th>
									<th>论文质量评分</th>
									<th>第一作者所在部门</th>
									<th>期刊名称</th>
									<th>期刊代码</th>
									<th>刊物级别</th>
									<th>收录情况</th>
									<th>资助项目</th>
									<th>操作</th>
								</tr>
							</thead>
							<tbody>
								<c:forEach items="${bList}" var="book" varStatus="status">
									<tr>
									   
									    <td>${status.index+1}</td>
										<td>${book.typeName}</td>
										<td>${book.bookName}</td>
										<td>${book.author}</td>
										<td>${book.press}</td>
										<td>${book.num}</td>
										<td>${book.part}</td>
										<td>${book.digest}</td>
										<td>${book.code}</td>
										<td>${book.grade}</td>
										<td>${book.shoulu}</td>
										<td>${book.project}</td>
										<td><button type="button" class="btn btn-info btn-xs"
										data-toggle="modal" onclick="borrowbook(${book.bid})">下载</button>
										</td>
									</tr>
								</c:forEach>
							</tbody>
						</table>
						${requestScope.pagation}
					</div>
				</div>
				<script type="text/javascript">
			    function borrowbook(bid) {
			    	con=confirm("是否下载?"); 
			    	if(con==true){
			    		location.href = "/books_MA/book?method=borrow&tip=1&bid="+bid;
			    	}
			    }
			    </script>
			</div>
	</div>

	<!-------------------------------------------------------------->

	<jsp:include page="../common/userInfo.jsp"></jsp:include>
	<jsp:include page="../common/js.jsp"></jsp:include>
</body>
</html>