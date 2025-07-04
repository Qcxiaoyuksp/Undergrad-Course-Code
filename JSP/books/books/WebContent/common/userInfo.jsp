<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<form class="form-horizontal" method="post"
	action="/books/user?method=updUserInfo">
	<!--保证样式水平不混乱-->
	<!-- 模态框（Modal） -->
	<div class="modal fade" id="updatepwd" tabindex="-1" role="dialog"
		aria-labelledby="myModalLabel" aria-hidden="true">
		<div class="modal-dialog">
			<div class="modal-content">
				<div class="modal-header">
					<button type="button" class="close" data-dismiss="modal"
						aria-hidden="true">&times;</button>
					<h4 class="modal-title" id="myModalLabel">修改密码</h4>
				</div>
				<div class="modal-body">
				
					<!--正文-->
					<input type="hidden" name="tip" value="1"> <input
						type="hidden" name="url" value="admin_user">
					<div class="form-group">
						<label for="firstname" class="col-sm-3 control-label">原密码</label>
						<div class="col-sm-7">
							<input type="password" class="form-control" name="password"
								id="oldPwd" placeholder="请输入原密码"> <label
								class="control-label" for="oldPwd" style="display: none"></label>
						</div>
					</div>

					<div class="form-group">
						<label for="firstname" class="col-sm-3 control-label">新密码</label>
						<div class="col-sm-7">
							<input type="password" class="form-control" name="password2"
								id="newPwd" placeholder="请输入新密码"> <label
								class="control-label" for="newPwd" style="display: none"></label>
						</div>
					</div>
				</div>
				<div class="modal-footer">
					<button type="button" class="btn btn-default"
						data-dismiss="modal">关闭</button>
					<button type="submit" class="btn btn-primary">修改</button>
				</div>
			</div>
			<!-- /.modal-content -->
		</div>
		<!-- /.modal -->
	</div>
</form>
<!-------------------------------------------------------------->

<!-------------------------个人资料模糊框------------------------------------->

<form class="form-horizontal" method="post"
	action="/books/user?method=updUserInfo">
	<!--保证样式水平不混乱-->
	<!-- 模态框（Modal） -->
	<div class="modal fade" id="updateinfo" tabindex="-1" role="dialog"
		aria-labelledby="ModalLabel" aria-hidden="true">
		<div class="modal-dialog">
			<div class="modal-content">
				<div class="modal-header">
					<button type="button" class="close" data-dismiss="modal"
						aria-hidden="true">&times;</button>
					<h4 class="modal-title" id="ModalLabel">个人资料</h4>
				</div>
				<div class="modal-body">

						<!--正文-->
					<input type="hidden" name="tip" value="2"> <input
						type="hidden" name="url" value="admin_user">
					<div class="form-group">
						<label for="firstname" class="col-sm-3 control-label">真实姓名</label>
						<div class="col-sm-7">
							<input type="text" class="form-control" id="name" name="name"
								placeholder="请输入您的真实姓名"
								value='${user.name}'> <label
								class="control-label" for="name" style="display: none"></label>
						</div>
					</div>

					<div class="form-group">
						<label for="firstname" class="col-sm-3 control-label">手机号</label>
						<div class="col-sm-7">
							<input type="text" class="form-control" id="phone" name="phone"
								placeholder="请输入您的手机号"
								value='${user.phone}'> <label
								class="control-label" for="phone" style="display: none"></label>
						</div>
					</div>
				</div>
				<div class="modal-footer">
					<button type="button" class="btn btn-default"
						data-dismiss="modal">关闭</button>
					<button type="submit" class="btn btn-primary">修改</button>
				</div>
			</div>
			<!-- /.modal-content -->
		</div>
		<!-- /.modal -->
	</div>
</form>