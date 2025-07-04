<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>角色管理</title>
    <#include "../common/link.ftl">
    <script>
        function moveSelected(src,target){
            $("."+target).append($("."+src+" option:selected"));
        }
        function moveAll(src,target){
            $("."+target).append($("."+src+" option"));
        }
        $(function () {
            $("#btn_submit").click(function () {
                $(".selfPermissions option").prop('selected',true);
                $("#editForm").submit();
            })

            //先把右边的权限id存放到ids数组中
            //遍历左边的权限,获取每个权限id,判断是否存在右边的ids数组中,如果存在则删除
            var ids = [];
            $(".selfPermissions option").each(function (index, ele) {
                ids.push($(ele).val())
            })
            $(".allPermissions option").each(function (index, ele) {
                var id = $(ele).val();
                if($.inArray(id,ids)>-1){
                    $(ele).remove();
                }
            })

        })
    </script>
</head>
<body class="hold-transition skin-blue sidebar-mini">
<div class="wrapper">
    <#include "../common/navbar.ftl">
    <!--菜单回显-->
    <c:set var="currentMenu" value="role"/>
    <#include "../common/menu.ftl">
    <div class="content-wrapper">
        <section class="content-header">
            <h1>角色编辑</h1>
        </section>
        <section class="content">
            <div class="box">
                <form class="form-horizontal" action="/role/saveOrUpdate.do" method="post" id="editForm">

                    <input type="hidden" value="${(role.id)!}" name="id">
                    <div class="form-group"  style="margin-top: 10px;">
                        <label for="name" class="col-sm-2 control-label">角色名称：</label>
                        <div class="col-sm-6">
                            <input type="text" class="form-control" id="name" name="name" value="${(role.name)!}" placeholder="请输入角色名称">
                        </div>
                    </div>

                    <div class="form-group">
                        <label for="sn" class="col-sm-2 control-label">角色编号：</label>
                        <div class="col-sm-6">
                            <input type="text" class="form-control" id="sn" name="sn" value="${(role.sn)!}" placeholder="请输入角色编号">
                        </div>
                    </div>
                    <div class="form-group " id="role">
                        <label for="role" class="col-sm-2 control-label">分配权限：</label><br/>
                        <div class="row" style="margin-top: 10px">
                            <div class="col-sm-2 col-sm-offset-2">
                                <select multiple class="form-control allPermissions" size="15">
                                    <#list permissions as p>
                                        <option value="${p.id}">${p.name}</option>
                                    </#list>
                                </select>
                            </div>

                            <div class="col-sm-1" style="margin-top: 60px;" align="center">
                                <div>

                                    <a type="button" class="btn btn-primary" style="margin-top: 10px" title="右移动"
                                       onclick="moveSelected('allPermissions', 'selfPermissions')">
                                        <span class="glyphicon glyphicon-menu-right"></span>
                                    </a>
                                </div>
                                <div>
                                    <a type="button" class="btn btn-primary " style="margin-top: 10px" title="左移动"
                                       onclick="moveSelected('selfPermissions', 'allPermissions')">
                                        <span class="glyphicon glyphicon-menu-left"></span>
                                    </a>
                                </div>
                                <div>
                                    <a type="button" class="btn btn-primary " style="margin-top: 10px" title="全右移动"
                                       onclick="moveAll('allPermissions', 'selfPermissions')">
                                        <span class="glyphicon glyphicon-forward"></span>
                                    </a>
                                </div>
                                <div>
                                    <a type="button" class="btn btn-primary " style="margin-top: 10px" title="全左移动"
                                       onclick="moveAll('selfPermissions', 'allPermissions')">
                                        <span class="glyphicon glyphicon-backward"></span>
                                    </a>
                                </div>
                            </div>
                            <div class="col-sm-2">
                                <select multiple class="form-control selfPermissions" size="15"  name="ids">
                                    <#list (role.permissions)! as p>
                                        <option value="${p.id}">${p.name}</option>
                                    </#list>
                                </select>
                            </div>


                        </div>
                    </div>
                    <div class="form-group">
                        <div class="col-sm-offset-1 col-sm-6">
                            <button id="btn_submit"  type="button" class="btn btn-primary">保存</button>
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
