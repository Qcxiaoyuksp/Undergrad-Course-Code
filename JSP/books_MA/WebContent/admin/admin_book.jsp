<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
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
		<!-- left, vertical navbar & content -->
		<div class="row">
			<!-- left, vertical navbar -->
			<jsp:include page="../common/left.jsp"></jsp:include>

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
									<!-- <input type="hidden" name="tip" value="1"> -->
									
									<div class="col-lg-7 form-group">
										<label class="col-lg-4 control-label" for="query_bname">论文信息</label>
										<div class="col-lg-8">
											<input class="form-control" id="bookName" name="word"					
												type="text" value="${word}"> <label class="control-label"
												for="query_bname" style="display: none;"></label>
										</div>
									</div>
									<div class="col-lg-3 form-group">

										<button type="submit" class="btn btn-primary" id="btn_query">查询</button>
									</div>
									<div class="col-lg-3 form-group">
										<button type="button" class="btn btn-primary" id="btn_add"
											data-toggle="modal" data-target="#addModal">添加论文</button>
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
									<th>质量评级</th>
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
										
										<td><button type="button" class="btn btn-warning btn-xs"
										data-toggle="modal" data-target="#updateModal" id="btn_update"
										onclick="showInfo2('${book.bid}','${book.tid}','${book.bookName}','${book.author}','${book.press}','${book.num}'
										,'${book.part}','${book.digest}','${book.code}','${book.grade}','${book.shoulu}','${book.project}')">
											修改</button>
									<button type="button" class="btn btn-danger btn-xs"
										onclick="deletebook(${book.bid})">删除</button></td>
									</tr>
								</c:forEach>
							</tbody>
						</table>
						${requestScope.pagation}
					</div>
				</div>
			</div>
		</div>
	</div>
	<script type="text/javascript">
		function showInfo2(bid, tid, name, autho, press, num) {
			document.getElementById("updateBookName").value = name;
			document.getElementById("updateAutho").value = autho;
			document.getElementById("updatePress").value = press;
			document.getElementById("updateBookType").value = tid;
			document.getElementById("updateNum").value = num;
			document.getElementById("updateBookId").value = bid;
			
			document.getElementById("updatePart").value = part;
			document.getElementById("updateDigest").value = digest;
			document.getElementById("updateCode").value = code;
			document.getElementById("updateGrade").value = grade;
			document.getElementById("updateShoulu").value = shoulu;
			document.getElementById("updateProject").value = project;
		}

		function deletebook(bid) {
			con = confirm("是否删除?");
			if(con == true) {
				location.href = "/books_MA/book?method=delBook&bid=" + bid;
			}
		}
	</script>

	<!-------------------------------------------------------------->

	<!-- 修改模态框（Modal） -->
	<form class="form-horizontal" method="post"
		action="/books_MA/book?method=updBook">
		<!--保证样式水平不混乱-->
		<div class="modal fade" id="updateModal" tabindex="-1" role="dialog"
			aria-labelledby="updateModalLabel" aria-hidden="true">
			<div class="modal-dialog">
				<div class="modal-content">
					<div class="modal-header">
						<button type="button" class="close" data-dismiss="modal"
							aria-hidden="true">&times;</button>
						<h4 class="modal-title" id="updateModalLabel">修改论文信息</h4>
					</div>
					<div class="modal-body">

						<!---------------------表单-------------------->

						<input name="bid" id="updateBookId" type="hidden"/>
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">论文名称</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="updateBookName" readonly="readonly"
									name="bookName" placeholder="请输入论文名称"> <label
									class="control-label" for="updateBookName"
									style="display: none;"></label>
							</div>
						</div>

						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">论文类型</label>
							<div class="col-sm-7">
								<select class="form-control" id="updateBookType" name="tid"
									onPropertyChange="showValue(this.value)">
									<option value="-1">请选择</option>
									<c:forEach items="${typeList}" var="type" varStatus="status">
										<option value="${type.tid}">${type.typeName}</option>
									</c:forEach>
								</select> 
								<label class="control-label" for="updateBookType"
									style="display: none;"></label>
							</div>
						</div>

						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">论文作者名称</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="updateAutho" readonly="readonly"
									name="author" placeholder="请输入论文作者名称"> <label
									class="control-label" for="updateAutho" style="display: none;"></label>
							</div>
						</div>

						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">论文认证</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="updatePress"
									name="press" placeholder="请输入出版社"> <label
									class="control-label" for="updatePress" style="display: none;"></label>
							</div>
						</div>
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">论文质量评级</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="updateNum"
									name="num" placeholder="请输入质量分数"> <label
									class="control-label" for="updatePress" style="display: none;"></label>
							</div>
						</div>
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">第一作者所在部门</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="updatePart"
									name="part" placeholder="请输入第一作者所在部门"> <label
									class="control-label" for="updatePress" style="display: none;"></label>
							</div>
						</div>
						
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">期刊名称</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="updateDigest"
									name="digest" placeholder="请输入期刊名称"> <label
									class="control-label" for="updatePress" style="display: none;"></label>
							</div>
						</div>
						
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">期刊代码</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="updateCode"
									name="code" placeholder="请输入期刊代码"> <label
									class="control-label" for="updatePress" style="display: none;"></label>
							</div>
						</div>
						
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">刊物级别</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="updateGrade"
									name="grade" placeholder="请输入刊物级别"> <label
									class="control-label" for="updatePress" style="display: none;"></label>
							</div>
						</div>
						
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">收录情况</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="updateShoulu"
									name="shoulu" placeholder="请输入收录情况"> <label
									class="control-label" for="updatePress" style="display: none;"></label>
							</div>
						</div>
						
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">资助项目</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="updateProject"
									name="project" placeholder="请输入资助项目"> <label
									class="control-label" for="updatePress" style="display: none;"></label>
							</div>
						</div>
						
						
						
						
					</div>
					<div class="modal-footer">
						<button type="button" class="btn btn-default" data-dismiss="modal">关闭</button>
						<button type="submit" class="btn btn-primary">修改</button>
					</div>
				</div>
				<!-- /.modal-content -->
			</div>
			<!-- /.modal -->
		</div>
	</form>
	<!-------------------------------------------------------------->

	<!--------------------------------------添加的模糊框------------------------>
	<form class="form-horizontal" method="post"  onsubmit="return checkAdd()"
		action="/books_MA/book?method=addBook">
		<!--保证样式水平不混乱-->
		<!-- 模态框（Modal） -->
		<div class="modal fade" id="addModal" tabindex="-1" role="dialog"
			aria-labelledby="myModalLabel" aria-hidden="true">
			<div class="modal-dialog">
				<div class="modal-content">
					<div class="modal-header">
						<button type="button" class="close" data-dismiss="modal"
							aria-hidden="true">&times;</button>
						<h5 style="text-align:center" id="msg"></h5>
					</div>
					<div class="modal-body">

						<!---------------------表单-------------------->


						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">论文名称</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="addBookName"
									required="required" name="bookName" placeholder="请输入论文名称">
								<label class="control-label" for="addBookName"
									style="display: none;"></label>
							</div>
						</div>

						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">论文类型</label>
							<div class="col-sm-7">
								<select class="form-control" id="addBookType" name="tid">
									<option value="无分类">请选择</option>
									<c:forEach items="${typeList}" var="type" varStatus="status">
										<option value="${type.tid}">${type.typeName}</option>
									</c:forEach>
								</select> 
								<label class="control-label" for="addBookType"
									style="display: none;"></label>
							</div>
						</div>

						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">论文作者名称</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="addAutho"
									required="required" name="author" placeholder="请输入论文作者名称">
								<label class="control-label" for="addAutho"
									style="display: none;"></label>
							</div>
						</div>

						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">论文认证</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="addPress"
									required="required" name="press" placeholder="请输入出版社">
								<label class="control-label" for="addPress"
									style="display: none;"></label>
							</div>
						</div>

						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">总质量评级</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="addNum"
									required="required" name="num" placeholder="请输入质量评分">
								<label class="control-label" for="addNum" style="display: none;"></label>
							</div>
						</div>
						
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">第一作者所在部门</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="addPart"
									required="required" name="part" placeholder="请输入第一作者所在部门">
								<label class="control-label" for="addPart" style="display: none;"></label>
							</div>
						</div>
						
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">期刊名称</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="addDigest"
									required="required" name="digest" placeholder="请输入期刊名称">
								<label class="control-label" for="addDigest" style="display: none;"></label>
							</div>
						</div>
						
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">期刊代码</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="addCode"
									required="required" name="code" placeholder="请输入期刊代码">
								<label class="control-label" for="addCode" style="display: none;"></label>
							</div>
						</div>
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">刊物级别</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="addGrade"
									required="required" name="grade" placeholder="请输入刊物级别">
								<label class="control-label" for="addGrade" style="display: none;"></label>
							</div>
						</div>
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">收录情况</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="addShoulu"
									required="required" name="shoulu" placeholder="请输入收录情况">
								<label class="control-label" for="addShoulu" style="display: none;"></label>
							</div>
						</div>
						
						<div class="form-group">
							<label for="firstname" class="col-sm-3 control-label">资助项目</label>
							<div class="col-sm-7">
								<input type="text" class="form-control" id="addProject"
									required="required" name="project" placeholder="请输入资助项目">
								<label class="control-label" for="addProject" style="display: none;"></label>
							</div>
						</div>

						<!---------------------表单-------------------->
					</div>
					<div class="modal-footer">
						<button type="button" class="btn btn-default" data-dismiss="modal">关闭</button>
						<button type="submit" class="btn btn-primary">添加</button>
					</div>
				</div>
				<!-- /.modal-content -->
			</div>
			<!-- /.modal -->
		</div>
	</form>
	<!--------------------------------------修改密码的模糊框------------------------>

	<jsp:include page="../common/userInfo.jsp"></jsp:include>
	<jsp:include page="../common/js.jsp"></jsp:include>
	<script type="text/javascript">
	var f=false;
	 $("#addBookName").blur(function(){
		 $.get("${pageContext.request.contextPath}/book?method=checkBook",{"bookName":$("#addBookName").val()},function(res){
			//json字符串转换对象
			var obj=JSON.parse(res);
			 if(obj.code==200){
				//账号可以被使用
				
				$("#msg").css({"color":"green"});
				$("#addBookName").css({"border-color":"green"});
				f=true;
			 }else{
				 $("#msg").css({"color":"red"});
					$("#addBookName").css({"border-color":"red"});
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