<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <!-- 引入 Bootstrap -->
    <script src="https://cdn.bootcss.com/jquery/2.2.4/jquery.min.js"></script>
    <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" rel="stylesheet">
    <!-- 引入 font-awesome -->
    <link href="https://cdn.bootcss.com/font-awesome/4.7.0/css/font-awesome.min.css" rel="stylesheet">
    <script src="https://cdn.bootcss.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
    <title>学术讲座管理系统</title>
</head>
<body>
<div class="container-fluid">
    <div class="row">
        <div class="col-sm-13">
            <!-- 顶部搜索部分 -->
            <div class="panel panel-default">
                <div class="panel-heading">搜索</div>
                <div class="panel-body">
                    <form role="form" class="form-inline" action="/academicLecture?method=search" method="post">
                        <div class="form-group">
                            <label for="name">字段：</label>
                            <select name="key" class="form-control">
								<option value="title">讲座题目</option>
								<option value="department_undertake">承办单位</option>
								<option value="speaker">主讲人</option>
								<option value="title_speaker">主讲人职称</option>
                            </select>
                        </div>
                        <div class="form-group" style="margin-left: 20px">
                            <label for="value">值：</label>
                            <input type="text" class="form-control" name="value" placeholder="字段值" maxlength="20" style="width: 200px">
                        </div>
                        <div class="form-group " style="margin-left: 20px">
                            <button type="submit" class="btn btn-info ">
										<span style="margin-right: 5px"
                                              class="glyphicon glyphicon-search" aria-hidden="true">
										</span>开始搜索
                            </button>
                        </div>
                        <div class="form-group " style="margin-left: 430px">
                            <button type="button" class="btn btn-default" data-toggle="modal" data-target="#addLectureModal">
										<span style="margin-right: 10px" class="" aria-hidden="true">
											<i class="fa fa-user-plus">添加学术讲座</i>
											</span>
                            </button>
                        </div>
                    </form>
                </div>
            </div>
            <!-- 列表展示-->
            <div class="table-responsive">
                <table class="table table-hover ">
                    <thead>
                    <tr>
                        <th>ID</th>
                        <th>讲座题目</th>
                        <th>承办单位</th>
                        <th>主讲人</th>
                        <th>主讲人所在部门</th>
                        <th>主讲人职称</th>
						<th>讲座日期</th>
						<th>时间</th>
						<th>地点</th>
                        <th>操作</th>
                    </tr>
                    </thead>
                    <tbody>
                    <c:forEach items="${list}" var="academicLecture">
                        <tr>
                            <td>${academicLecture.id}</td>
                            <td>${academicLecture.title}</td>
                            <td>${academicLecture.department_undertake}</td>
                            <td>${academicLecture.speaker}</td>
                            <td>${academicLecture.department_speaker}</td>
                            <td>${academicLecture.title_speaker}</td>
							<td>${academicLecture.data_lecture}</td>
							<td>${academicLecture.time}</td>
							<td>${academicLecture.address}</td>

                            <td>
                                <div class="btn-group">
                                    <button type="button" class="btn btn-default "
                                            data-id="${academicLecture.id}"
                                            data-title="${academicLecture.title}"
                                            data-department_undertake="${academicLecture.department_undertake}"
                                            data-speaker="${academicLecture.speaker}"
                                            data-department_speaker="${academicLecture.department_speaker}"
                                            data-title_speaker="${academicLecture.title_speaker}"
											data-data_lecture="${academicLecture.data_lecture}"
											data-time="${academicLecture.time}"
											data-address="${academicLecture.address}"
                                            data-toggle="modal"
                                            data-target="#updateUserModal">
                                        <i class="fa fa-user-o">修改</i>
                                    </button>

                                    <button type="button" class="btn btn-danger "
                                            data-id="${academicLecture.id}" data-toggle="modal"
                                            onclick="" data-target="#delUserModal">
                                        <i class="fa fa-user-times">删除</i>
                                    </button>
                                </div>
                            </td>
                        </tr>
                    </c:forEach>
                    </tbody>
                </table>
                <!-- add框示例（Modal） -->
                <form method="post" action="/academicLecture?method=save" class="form-horizontal" style="margin-top: 0px" role="form"
                      id="form_data" style="margin: 20px;">
                    <div class="modal fade" id="addLectureModal" tabindex="-1"
                         role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
                        <div class="modal-dialog">
                            <div class="modal-content">
                                <div class="modal-header">
                                    <button type="button" class="close" data-dismiss="modal"
                                            aria-hidden="true">x</button>
                                    <h4 class="modal-title" id="myModalLabel">添加学术讲座信息</h4>
                                </div>
                                <div class="modal-body">
                                    <form class="form-horizontal" role="form">
                                        <div class="form-group">
                                            <label for="user_id" class="col-sm-3 control-label">讲座题目</label>
                                            <div class="col-sm-9">
                                                <input type="text" required class="form-control" id="title"
                                                       name="title" placeholder="请输入讲座题目">
                                            </div>
                                        </div>

                                        <div class="form-group">
                                            <label for="user_id" class="col-sm-3 control-label">承办单位</label>
                                            <div class="col-sm-9">
                                                <input type="text" required class="form-control" id="department_undertake"
                                                       name="department_undertake" value="" placeholder="请输入承办单位">
                                            </div>
                                        </div>

                                        <div class="form-group">
                                            <label for="user_id" class="col-sm-3 control-label">主讲人</label>
                                            <div class="col-sm-9">
                                                <input type="text" required class="form-control" id="speaker"
                                                       name="speaker" value="" placeholder="请输入主讲人姓名">
                                            </div>
                                        </div>

										<div class="form-group">
											<label for="user_id" class="col-sm-3 control-label">主讲人所在部门</label>
											<div class="col-sm-9">
												<input type="text" required class="form-control" id="department_speaker"
													   name="department_speaker" value="" placeholder="请输入主讲人所在部门">
											</div>
										</div>

										<div class="form-group">
											<label for="user_id" class="col-sm-3 control-label">主讲人职称</label>
											<div class="col-sm-9">
												<select name="title_speaker" class="form-control">
													<option value="教授">教授</option>
													<option value="副教授">副教授</option>
													<option value="讲师">讲师</option>
													<option value="助教">助教</option>
												</select>
											</div>
										</div>

                                        <%--<div class="form-group">--%>
                                        <%--    <label for="user_id" class="col-sm-3 control-label">性别</label>--%>
                                        <%--    <div class="col-sm-9">--%>
                                        <%--        <input type="radio" checked value="男" class="gender"--%>
                                        <%--               name="gender"> 男--%>
                                        <%--        &nbsp;&nbsp;&nbsp;<input type="radio" value="女" class="gender"--%>
                                        <%--                                 name="gender"> 女--%>
                                        <%--    </div>--%>
                                        <%--</div>--%>

                                        <%--<div class="form-group">--%>
                                        <%--    <label for="user_id" class="col-sm-3 control-label">联系电话</label>--%>
                                        <%--    <div class="col-sm-9">--%>
                                        <%--        <input type="text" required class="form-control" id="telephone"--%>
                                        <%--               name="telephone" value="" placeholder="请输入联系电话">--%>
                                        <%--    </div>--%>
                                        <%--</div>--%>

										<div class="form-group">
											<label for="user_id" class="col-sm-3 control-label">讲座日期</label>
											<div class="col-sm-9">
												<input type="date" required name="data_lecture" value="" id="data_lecture"
													   class="form-control" placeholder=""/>
											</div>
										</div>

										<div class="form-group">
											<label for="user_id" class="col-sm-3 control-label">时间</label>
											<div class="col-sm-9">
												<input type="time" required name="time" value="" id="time"
													   class="form-control" placeholder=""/>
											</div>
										</div>

										<div class="form-group">
											<label for="user_id" class="col-sm-3 control-label">地点</label>
											<div class="col-sm-9">
												<input type="text" required class="form-control" id="address"
													   name="address" value="" placeholder="请输入地点">
											</div>
										</div>

                                    </form>
                                </div>
                                <div class="modal-footer">
                                    <button type="button" class="btn btn-default" data-dismiss="modal">取消</button>
                                    <button type="submit" class="btn btn-primary">提交</button>
                                </div>
                            </div>
                        </div>
                    </div>
                </form>

                <!-- update框示例（Modal） -->
                <form method="post" action="/academicLecture?method=update" class="form-horizontal" style="margin-top: 0px" role="form"
                      id="form_data" style="margin: 20px;">
                    <div class="modal fade" id="updateUserModal" tabindex="-1"
                         role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
                        <div class="modal-dialog">
                            <div class="modal-content">
                                <div class="modal-header">
                                    <button type="button" class="close" data-dismiss="modal"
                                            aria-hidden="true">x</button>
                                    <h4 class="modal-title" id="myModalLabel">用户信息</h4>
                                </div>
                                <div class="modal-body">
                                    <form class="form-horizontal" role="form">
                                        <div class="form-group">
                                            <label for="user_id" class="col-sm-3 control-label">ID</label>
                                            <div class="col-sm-9">
                                                <input type="text" readonly required class="form-control" id="id"
                                                       name="id">
                                            </div>
                                        </div>

										<div class="form-group">
											<label for="user_id" class="col-sm-3 control-label">讲座题目</label>
											<div class="col-sm-9">
												<input type="text" required class="form-control" id="title"
													   name="title" placeholder="请输入讲座题目">
											</div>
										</div>

										<div class="form-group">
											<label for="user_id" class="col-sm-3 control-label">承办单位</label>
											<div class="col-sm-9">
												<input type="text" required class="form-control" id="department_undertake"
													   name="department_undertake" value="" placeholder="请输入承办单位">
											</div>
										</div>

										<div class="form-group">
											<label for="user_id" class="col-sm-3 control-label">主讲人</label>
											<div class="col-sm-9">
												<input type="text" required class="form-control" id="speaker"
													   name="speaker" value="" placeholder="请输入主讲人姓名">
											</div>
										</div>

										<div class="form-group">
											<label for="user_id" class="col-sm-3 control-label">主讲人所在部门</label>
											<div class="col-sm-9">
												<input type="text" required class="form-control" id="department_speaker"
													   name="department_speaker" value="" placeholder="请输入主讲人所在部门">
											</div>
										</div>

										<div class="form-group">
											<label for="user_id" class="col-sm-3 control-label">主讲人职称</label>
											<div class="col-sm-9">
												<select name="title_speaker" class="form-control">
													<option value="教授">教授</option>
													<option value="副教授">副教授</option>
													<option value="讲师">讲师</option>
													<option value="助教">助教</option>
												</select>
											</div>
										</div>

										<div class="form-group">
											<label for="user_id" class="col-sm-3 control-label">讲座日期</label>
											<div class="col-sm-9">
												<input type="date" required name="data_lecture" value="" id="data_lecture"
													   class="form-control" placeholder="请输入时间"/>
											</div>
										</div>

										<div class="form-group">
											<label for="user_id" class="col-sm-3 control-label">时间</label>
											<div class="col-sm-9">
												<input type="time" required name="time" value="" id="time"
													   class="form-control" placeholder="请输入时间"/>
											</div>
										</div>

										<div class="form-group">
											<label for="user_id" class="col-sm-3 control-label">地点</label>
											<div class="col-sm-9">
												<input type="text" required class="form-control" id="address"
													   name="address" value="" placeholder="请输入地点">
											</div>
										</div>

                                        <%--<div class="form-group">--%>
                                        <%--    <label for="user_id" class="col-sm-3 control-label">讲座题目</label>--%>
                                        <%--    <div class="col-sm-9">--%>
                                        <%--        <input type="text" required class="form-control" id="title"--%>
                                        <%--               name="title" placeholder="请输入讲座题目">--%>
                                        <%--    </div>--%>
                                        <%--</div>--%>

                                        <%--<div class="form-group">--%>
                                        <%--    <label for="user_id" class="col-sm-3 control-label">承办单位</label>--%>
                                        <%--    <div class="col-sm-9">--%>
                                        <%--        <input type="text" required class="form-control" id="department_undertake"--%>
                                        <%--               name="department_undertake" value="" placeholder="请输入承办单位">--%>
                                        <%--    </div>--%>
                                        <%--</div>--%>

                                        <%--<div class="form-group">--%>
                                        <%--    <label for="user_id" class="col-sm-3 control-label">姓名</label>--%>
                                        <%--    <div class="col-sm-9">--%>
                                        <%--        <input type="text" required class="form-control" id="name"--%>
                                        <%--               name="name" value="" placeholder="请输入姓名">--%>
                                        <%--    </div>--%>
                                        <%--</div>--%>

                                        <%--<div class="form-group">--%>
                                        <%--    <label for="user_id" class="col-sm-3 control-label">性别</label>--%>
                                        <%--    <div class="col-sm-9">--%>
                                        <%--        <input type="radio" checked value="男" class="gender"--%>
                                        <%--               name="gender"> 男--%>
                                        <%--        &nbsp;&nbsp;&nbsp;<input type="radio" value="女" class="gender"--%>
                                        <%--                                 name="gender"> 女--%>
                                        <%--    </div>--%>
                                        <%--</div>--%>

                                        <%--<div class="form-group">--%>
                                        <%--    <label for="user_id" class="col-sm-3 control-label">联系电话</label>--%>
                                        <%--    <div class="col-sm-9">--%>
                                        <%--        <input type="text" required class="form-control" id="telephone"--%>
                                        <%--               name="telephone" value="" placeholder="">--%>
                                        <%--    </div>--%>
                                        <%--</div>--%>
                                    </form>
                                </div>
                                <div class="modal-footer">
                                    <button type="button" class="btn btn-default" data-dismiss="modal">取消</button>
                                    <button type="submit" class="btn btn-primary">提交</button>
                                </div>
                            </div>
                        </div>
                    </div>
                </form>

                <!-- 删除模态框示例（Modal） -->
                <form method="post" action="/academicLecture?method=delete"
                      class="form-horizontal" style="margin-top: 0px" role="form"
                      id="form_data" style="margin: 20px;">
                    <div class="modal fade" id="delUserModal" tabindex="-1"
                         role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
                        <div class="modal-dialog">
                            <div class="modal-content">
                                <div class="modal-header">
                                    <button type="button" class="close" data-dismiss="modal"
                                            aria-hidden="true">×</button>
                                    <h4 class="modal-title" id="myModalLabel">用户信息</h4>
                                </div>
                                <div class="modal-body">
                                    <form class="form-horizontal" role="form">
                                        <div class="form-group">
                                            <div class="col-sm-9">
                                                <h3 class="col-sm-18 control-label" id="deleteLabel">删除信息</h3>
                                                <input type="hidden" class="form-control" id="tab"
                                                       name="tab" placeholder="" value="dor_admin"> <input
                                                    type="hidden" class="form-control" id="id"
                                                    name="id" placeholder="">
                                            </div>
                                        </div>
                                    </form>
                                </div>
                                <div class="modal-footer">
                                    <button type="button" class="btn btn-default" data-dismiss="modal">取消</button>
                                    <button type="submit" class="btn btn-danger">删除</button>
                                    <span id="tip"> </span>
                                </div>
                            </div>
                        </div>
                    </div>
                </form>
            </div>
        </div>
    </div>
</div>

<script>
    $('#updateUserModal').on('show.bs.modal', function(event) {
        var button = $(event.relatedTarget)
        var id = button.data('id')
        var title = button.data('title')
        var department_undertake = button.data('department_undertake')
        var speaker = button.data('speaker')
        var department_speaker = button.data('department_speaker')
        var title_speaker = button.data('title_speaker')
        var data_lecture = button.data('data_lecture')
        var time = button.data('time')
        var address = button.data('address')
        var modal = $(this)

        modal.find('.modal-title').text('修改学术讲座信息')
        modal.find('#id').val(id)
        modal.find('#title').val(title)
        modal.find('#department_undertake').val(department_undertake)
        modal.find('#speaker').val(speaker)
        modal.find('#department_speaker').val(department_speaker)
        modal.find('#title_speaker').val(title_speaker)
        modal.find('#data_lecture').val(data_lecture)
        modal.find('#time').val(time)
        // var list = modal.find('.gender')
        // for(var i=0;i<list.length;i++){
        //     if(gender == $(list.get(i)).val()){
        //         $(list.get(i)).prop('checked',true)
        //     }
        // }
        modal.find('#address').val(address)
    })

    $('#delUserModal').on('show.bs.modal', function(event) {
        var button = $(event.relatedTarget)
        var id = button.data('id')
        var modal = $(this)
        modal.find('.modal-title').text('删除学术讲座信息')
        modal.find('#deleteLabel').text('是否删除ID为  ' + id + ' 的信息')
        modal.find('#id').val(id)
    })
</script>

</body>

</html>