<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>员工管理</title>
    <#include "../common/link.ftl">
    <script>
        //角色左移右移(移选中)
        function moveSelected(src,target){
            $("."+target).append($("."+src+" option:selected"))
        }
        //角色左移右移(移全部)
        function moveAll(src,target){
            $("."+target).append($("."+src+" option"))
        }

        $(function () {
            var roleDiv;
            //监听超管复选框的点击事件 checkbox
            $("#admin").click(function () {
                var checked = $(this).prop("checked");
                if(checked){
                    roleDiv = $("#role").detach(); //detach() 会保留所有绑定的事件、附加的数据
                }else{
                    //把角色div放到超管的div后边
                    $("#adminDiv").after(roleDiv);
                }
            })

            //判断是否管理员
            if($("#admin").prop("checked")){
                roleDiv = $("#role").detach();
            }


            //把右边的所有角色的id存放到数组中(ids)
            var ids = [];
            $(".selfRoles option").each(function (index, ele) {
                ids.push($(ele).val())
            })

            //遍历左边的角色,获取每个角色id,判断是否存在ids数组,如果存在则删除该条数据
            $(".allRoles option").each(function (index, ele) {
                var id = $(ele).val();
                if($.inArray(id,ids)>-1){
                    $(ele).remove();
                }
            })

            //表单数据验证
            $("#editForm").bootstrapValidator({
                feedbackIcons: { //图标
                    valid: 'glyphicon glyphicon-ok',
                    invalid: 'glyphicon glyphicon-remove',
                    validating: 'glyphicon glyphicon-refresh'
                },
                fields:{ //配置要验证的字段
                    //新增才需要验证用户名,编辑不需要
                    <#if !employee??>
                        name:{
                            validators:{ //验证的规则
                                notEmpty:{ //不能为空
                                    message:"用户名必填" //错误时的提示信息
                                },
                                stringLength: {
                                    min: 1,
                                    max: 5
                                },
                                remote: { //远程验证
                                    type: 'POST', //请求方式
                                    url: '/employee/checkName.do', //请求地址
                                    data:{
                                        id:$("#id").val()
                                    },
                                    message: '用户名已经存在', //验证不通过时的提示信息
                                    delay: 1000 //输入内容1秒后发请求
                                },
                            }
                        },
                    </#if>
                   /* password:{
                        validators:{
                            notEmpty:{ //不能为空
                                message:"密码必填" //错误时的提示信息
                            },
                        }
                    },
                    repassword:{
                        validators:{
                            notEmpty:{ //不能为空
                                message:"密码必填" //错误时的提示信息
                            },
                            identical: {
                                field: 'password',
                                message: '两次输入的密码必须相同'
                            },
                        }
                    },
                    email: {
                        validators: {
                            emailAddress: {}
                        }
                    },
                    age:{
                        validators: {
                            between: {
                                min: 18,
                                max: 60
                            }
                        }
                    }*/

                }
            }).on('success.form.bv', function(e) { //表单所有数据验证通过后执行里面的代码
                //禁止原本的表单提交
                e.preventDefault();
                //设置右边的所有option为选中的状态
                $(".selfRoles option").prop('selected',true);

                $("#editForm").ajaxSubmit(function (data) {
                    if(data.success){ //用alert或者popup都可以
                        $.messager.alert("温馨提示","保存成功!2s后自动关闭")
                        window.setTimeout(function () {
                            window.location.href = "/employee/list.do";
                        },2000)
                    }else{
                        $.messager.popup(data.msg)
                    }
                })
            });


            //监听保存按钮事件
            /* $("#submitBtn").click(function () {
                 //设置右边的所有option为选中的状态
                 $(".selfRoles option").prop('selected',true);
                 //提交表单
                 $("#editForm").submit();
             })
 */






        })




    </script>
</head>
<body class="hold-transition skin-blue sidebar-mini">
<div class="wrapper">
    <#include "../common/navbar.ftl">
    <!--菜单回显-->
    <#assign currentMenu="employee"/>
    <#include "../common/menu.ftl">
    <div class="content-wrapper">
        <section class="content-header">
            <h1>员工编辑</h1>
        </section>
        <section class="content">
            <div class="box">
                <form class="form-horizontal" action="/employee/saveOrUpdate.do" method="post" id="editForm">
                    <input type="hidden" value="${(employee.id)!}" name="id" >
                    <div class="form-group" style="margin-top: 10px;">
                        <label for="name" class="col-sm-2 control-label">用户名：</label>
                        <div class="col-sm-6">
                            <input type="text" class="form-control"
                                  <#if employee??>
                                         readonly
                                  </#if>
                                   id="name" name="name" value="${(employee.name)!}" placeholder="请输入用户名">
                        </div>
                    </div>
                    <#if !employee?? > <!--新增的时候需要显示密码输入框-->
                         <div class="form-group">
                             <label for="password" class="col-sm-2 control-label">密码：</label>
                             <div class="col-sm-6">
                                 <input type="password" class="form-control" id="password" name="password" placeholder="请输入密码">
                             </div>
                         </div>
                        <div class="form-group">
                            <label for="repassword" class="col-sm-2 control-label">验证密码：</label>
                            <div class="col-sm-6">
                                <input type="password" class="form-control" id="repassword" name="repassword" placeholder="再输入一遍密码">
                            </div>
                        </div>
                    </#if>

                    <div class="form-group">
                        <label for="email" class="col-sm-2 control-label">电子邮箱：</label>
                        <div class="col-sm-6">
                            <input type="text" class="form-control" id="email" name="email" value="${(employee.email)!}" placeholder="请输入邮箱">
                        </div>
                    </div>
                    <div class="form-group">
                        <label for="age" class="col-sm-2 control-label">年龄：</label>
                        <div class="col-sm-6">
                            <input type="text" class="form-control" id="age" name="age" value="${(employee.age)!}" placeholder="请输入年龄">
                        </div>
                    </div>
                    <div class="form-group">
                        <label for="dept" class="col-sm-2 control-label">部门：</label>
                        <div class="col-sm-6">
                            <select class="form-control" id="dept" name="dept.id">
                                <#list depts as d>
                                    <option value="${d.id}">${d.name}</option>
                                </#list>
                            </select>
                            <script>
                                $("#dept").val(${(employee.dept.id)!})
                            </script>
                        </div>
                    </div>
                    <div class="form-group" id="adminDiv">
                        <label for="admin" class="col-sm-2 control-label">超级管理员：</label>
                        <div class="col-sm-6"style="margin-left: 15px;">
                            <input type="checkbox" id="admin" name="admin" class="checkbox">
                            <#if (employee.admin)!false >
                                <script>
                                    $("#admin").prop("checked", true);
                                </script>
                            </#if>
                        </div>
                    </div>
                    <div class="form-group " id="role">
                        <label for="role" class="col-sm-2 control-label">分配角色：</label><br/>
                        <div class="row" style="margin-top: 10px">
                            <div class="col-sm-2 col-sm-offset-2">
                                <select multiple class="form-control allRoles" size="15">
                                    <#list roles as r>
                                        <option value="${r.id}">${r.name}</option>
                                    </#list>
                                </select>
                            </div>

                            <div class="col-sm-1" style="margin-top: 60px;" align="center">
                                <div>

                                    <a type="button" class="btn btn-primary  " style="margin-top: 10px" title="右移动"
                                       onclick="moveSelected('allRoles', 'selfRoles')">
                                        <span class="glyphicon glyphicon-menu-right"></span>
                                    </a>
                                </div>
                                <div>
                                    <a type="button" class="btn btn-primary " style="margin-top: 10px" title="左移动"
                                       onclick="moveSelected('selfRoles', 'allRoles')">
                                        <span class="glyphicon glyphicon-menu-left"></span>
                                    </a>
                                </div>
                                <div>
                                    <a type="button" class="btn btn-primary " style="margin-top: 10px" title="全右移动"
                                       onclick="moveAll('allRoles', 'selfRoles')">
                                        <span class="glyphicon glyphicon-forward"></span>
                                    </a>
                                </div>
                                <div>
                                    <a type="button" class="btn btn-primary " style="margin-top: 10px" title="全左移动"
                                       onclick="moveAll('selfRoles', 'allRoles')">
                                        <span class="glyphicon glyphicon-backward"></span>
                                    </a>
                                </div>
                            </div>

                            <div class="col-sm-2">
                                <select multiple class="form-control selfRoles" size="15" name="ids">
                                    <#list (employee.roles)! as r>
                                        <option value="${r.id}">${r.name}</option>
                                    </#list>
                                </select>
                            </div>
                        </div>
                    </div>

                    <div class="form-group">
                        <div class="col-sm-offset-1 col-sm-6">
                            <!--button如果是在form表单内部,不写type默认就是submit-->
                            <!-- 验证插件只支持submit按钮提交-->
                            <button id="submitBtn" type="submit" class="btn btn-primary">保存</button>
                            <button type="reset" class="btn btn-danger">重置</button>
                        </div>
                    </div>
                </form>
            </div>
        </section>
    </div>
    <#include "../common/footer.ftl">
</div>
</body>
</html>
