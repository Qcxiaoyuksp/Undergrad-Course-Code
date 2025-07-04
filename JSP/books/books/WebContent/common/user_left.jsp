<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<!-- 用户端左侧导航栏 -->
<div class="col-md-2 bootstrap-admin-col-left">
	<ul class="nav navbar-collapse collapse bootstrap-admin-navbar-side">
		<li><a href="/books/book?method=listByPage"><i
				class="glyphicon glyphicon-chevron-right"></i> 图书查询</a></li>
		<li><a href="/books/history?method=list"><i
				class="glyphicon glyphicon-chevron-right"></i> 借阅信息</a></li>
		<li><a href="/books/history?method=backList"><i
				class="glyphicon glyphicon-chevron-right"></i> 借阅历史</a></li>
	</ul><br><br>
	<ul class="nav navbar-collapse collapse bootstrap-admin-navbar-side">
		<li><a href="/books/book?method=rank"><i
				class="glyphicon glyphicon-chevron-right"></i> 热门推荐</a></li>
		<li><a href="/books/user?method=rank"><i
				class="glyphicon glyphicon-chevron-right"></i> 最佳读者</a></li>
	</ul><br><br>
	<ul class="nav navbar-collapse collapse bootstrap-admin-navbar-side">
		<li><a href="/books/user/feedback.jsp"><i
				class="glyphicon glyphicon-chevron-right"></i> 问题反馈</a></li>
	</ul>
</div>
