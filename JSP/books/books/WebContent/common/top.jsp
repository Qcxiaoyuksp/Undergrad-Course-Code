<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<nav class="navbar navbar-inverse navbar-fixed-top bootstrap-admin-navbar bootstrap-admin-navbar-under-small"
	role="navigation">
	<div class="container">
		<div class="row">
			<div class="col-lg-12">
				<div class="collapse navbar-collapse main-navbar-collapse">
					<a class="navbar-brand" href="admin.jsp"><strong>欢迎使用图书馆管理系统</strong></a>
					<ul class="nav navbar-nav navbar-right">
						<li class="dropdown"><a href="#" role="button"
							class="dropdown-toggle" data-hover="dropdown"> <i
								class="glyphicon glyphicon-user"></i> 欢迎您，${userDB.name}
									(${userDB.account})
								<i class="caret"></i></a>
							<ul class="dropdown-menu">
								<li><a href="#updateinfo" data-toggle="modal">个人资料</a></li>
								<li role="presentation" class="divider"></li>
								<li><a href="#updatepwd" data-toggle="modal">修改密码</a></li>
								<li role="presentation" class="divider"></li>
								<li><a href="/books/login.jsp">退出</a></li>
							</ul>
						</li>
					</ul>
				</div>
			</div>
		</div>
	</div>
</nav>