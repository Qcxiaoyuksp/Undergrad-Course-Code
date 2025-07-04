<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%
	if (session.getAttribute("userDB") == null){
		response.sendRedirect(request.getContextPath() + "/login.jsp");
	}	
%>
<!DOCTYPE HTML>
<html>
<head>
	<title>论文管理系统</title>
	<jsp:include page="common/css.jsp"></jsp:include>	
	<style>
		body {
			background-image: url("static/images/03.jpg");
		}
	</style>
</head>

<body class="bootstrap-admin-with-small-navbar">
	<jsp:include page="common/top.jsp"></jsp:include>
	<div class="container">
		<div class="row">
			<c:if test="${userDB.role == 1}">
				<jsp:include page="common/user_left.jsp"></jsp:include>			
			</c:if>
			<c:if test="${userDB.role == 2}">
				<jsp:include page="common/left.jsp"></jsp:include>			
			</c:if>
			<!-- content -->
			<div class="col-md-10">
				<div class="row">
					<div class="col-md-6">
						<div class="panel panel-default">
							<div class="panel-heading">
								<div class="text-muted bootstrap-admin-box-title">论文查询</div>
							</div>
							<div class="bootstrap-admin-panel-content">
								<ul>
									<li>根据论文名称、作者、类别查询论文信息</li>
									<li>可查询论文的编号、名称、分类、作者、发行期刊等</li>
								</ul>
							</div>
						</div>
					</div>
					<!-- 判断用户是否登录 -->
					<div class="col-md-6">
						<div class="panel panel-default">
							<div class="panel-heading">
								<div class="text-muted bootstrap-admin-box-title">学术性论文</div>
							</div>
							<div class="bootstrap-admin-panel-content">
								<ul>
									<li>学术性 学术论文要求作者在立论上不能带有个人偏见,也不能主观臆造,
									在撰写论文时要从客观和实际出发,这样才能得出符合实际的结论。当运用论据时,
									要用最充分、有力的论据作为论证的基础,
									在论证时,要经过深思熟虑,严格地论证</li>
								</ul>
							</div>
						</div>
					</div>
				</div>
				
				<div class="row">
					<div class="col-md-6">
						<div class="panel panel-default">
							<div class="panel-heading">
								<div class="text-muted bootstrap-admin-box-title">热门推荐</div>
							</div>
							<div class="bootstrap-admin-panel-content">
								<ul>
									<li>在形式上，学术论文属于议论文，但学术论文不同于议论文，它有自己的理论体系，
									并非单纯罗列材料，
									需要对大量事实、材料进行分析、研究，从感性认识上升到理性认识。</li>
								</ul>
							</div>
						</div>
					</div>
					<div class="col-md-6">
						<div class="panel panel-default">
							<div class="panel-heading">
								<div class="text-muted bootstrap-admin-box-title">下载历史</div>
							</div>
							<div class="bootstrap-admin-panel-content">
								<ul>
									<li>查询下载历史，下载时间等具体信息</li>
								</ul>
							</div>
						</div>
					</div>
				</div>
				
				<div class="row">
					<div class="col-md-6">
						<div class="panel panel-default">
							<div class="panel-heading">
								<div class="text-muted bootstrap-admin-box-title">优秀作者</div>
							</div>
							<div class="bootstrap-admin-panel-content">
								<ul>
									<li>展示每一位已知读者的下载量，以及用户的基本信息</li>
								</ul>
							</div>
						</div>
					</div>
					<div class="col-md-6">
						<div class="panel panel-default">
							<div class="panel-heading">
								<div class="text-muted bootstrap-admin-box-title">问题反馈</div>
							</div>
							<div class="bootstrap-admin-panel-content">
								<ul>
									<li>有问题请留下您的联系方式，我们会记录在库并及时反馈</li>
								</ul>
							</div>
						</div>
					</div>
				</div>
				
				
				<div class="row">
					<div class="col-md-6">
						<div class="panel panel-default">
							<div class="panel-heading">
								<div class="text-muted bootstrap-admin-box-title">创造性论文</div>
							</div>
							<div class="bootstrap-admin-panel-content">
								<ul>
									<li>科研是探索新知识，创新是科研的生命。</li>
									<li>论文的创造性在于作者在撰写学术论文时要有自己独到的见解。</li>
									<li>科学的方法主要是发现新现象，建立新理论，旧的科学理论必然要推翻旧的科学理论，因为科学方法主要是发现新现象，建立新的理论。
									因此，没有创造性的学术论文是没有科学价值的。

</li>
								</ul>
							</div>
						</div>
					</div>
					<div class="col-md-6">
						<div class="panel panel-default">
							<div class="panel-heading">
								<div class="text-muted bootstrap-admin-box-title">理论性</div>
							</div>
							<div class="bootstrap-admin-panel-content">
								<ul>
									<li>学术论文的理论性是指论文写作时，用通俗易懂的语言来表达科学道理，
									既要做到文从字顺，又要准确、鲜明、和谐、力求生动。</li>
								</ul>
							</div>
						</div>
					</div>
				</div>
				
				
			</div>
		</div>
	</div>

	<!-------------------------------------------------------------->

	<jsp:include page="common/userInfo.jsp"></jsp:include>
	<jsp:include page="common/js.jsp"></jsp:include>
</body>
</html>