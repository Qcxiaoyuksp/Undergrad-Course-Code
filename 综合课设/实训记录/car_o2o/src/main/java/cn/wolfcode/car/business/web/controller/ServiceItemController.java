package cn.wolfcode.car.business.web.controller;

import cn.wolfcode.car.base.domain.User;
import cn.wolfcode.car.base.service.IUserService;
import cn.wolfcode.car.business.domain.ServiceItem;
import cn.wolfcode.car.business.query.ServiceItemQuery;
import cn.wolfcode.car.business.service.IServiceItemService;
import cn.wolfcode.car.common.base.page.TablePageInfo;
import cn.wolfcode.car.common.web.AjaxResult;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import java.math.BigDecimal;
import java.util.List;

@Controller
@RequestMapping("/business/serviceItem")
public class ServiceItemController {
    // 模板前缀
    private static final String prefix = "/business/serviceItem";
    @Autowired
    private IServiceItemService serviceItemService;
    @Autowired
    private IUserService userService;
    /**********************  进入页面 start *****************************/
    // 进入养修服务单项列表
    @RequestMapping("/listPage")
    public String list(){
        return prefix + "/list";
    }
    // 进入养修服务单项新增页面
    @RequestMapping("/addPage")
    public String addPage(){
        return prefix + "/add";
    }
    // 进入养修服务单项编辑页面
    @RequestMapping("/editPage")
    public String editPage(Long id, Model model){
        ServiceItem serviceItem = serviceItemService.get(id);
        model.addAttribute("serviceItem",serviceItem);
        return prefix + "/edit";
    }
    // 进入发起审核列表
    @RequestMapping("/auditPage")
    public String auditPage(Long id,Model model){
        // 首先根据 id 查询出对应的服务单项(套餐)，用于回显前三组数据
        ServiceItem serviceItem = serviceItemService.get(id);
        model.addAttribute("serviceItem",serviceItem);
        /*if(ServiceItem.CARPACKAGE_NO.equals(serviceItem.getCarPackage())){
            throw new BusinessException("必须是套餐才可以进行审核");
        }
        if(!(ServiceItem.AUDITSTATUS_INIT.equals(serviceItem.getAuditStatus())
            || ServiceItem.AUDITSTATUS_REPLY.equals(serviceItem.getAuditStatus()))) {
            throw new BusinessException("只有审核中和重新调整状态才能发起审核");
        }  */
        // 查询审批人。(K 在角色中就是店长，名字一会需要与前台对应)
        List<User> shopOwners = userService.queryByRoleKey("shopOwner");
        model.addAttribute("shopOwners",shopOwners);
        // 若金额 >= 3000，我们还需要第二审批人-财务
        if(serviceItem.getDiscountPrice().compareTo(new BigDecimal("3000")) >= 0){
            // 大于等于 3000 追加财务
            List<User> finances = userService.queryByRoleKey("financial");
            model.addAttribute("finances",finances);
        }
        return prefix + "/audit";
    }
    /**********************  进入页面 end *****************************/
    @RequestMapping("/query")
    @ResponseBody
    public TablePageInfo<ServiceItem> query(ServiceItemQuery qo){
        return serviceItemService.query(qo);
    }
    // 养修服务单项新增功能
    @RequestMapping("/add")
    @ResponseBody
    public AjaxResult add(ServiceItem serviceItem){
        serviceItemService.save(serviceItem);
        return AjaxResult.success();
    }
    // 养修服务单项编辑功能
    @RequestMapping("/edit")
    @ResponseBody
    public AjaxResult edit(ServiceItem serviceItem){
        serviceItemService.update(serviceItem);
        return AjaxResult.success();
    }
    // 上架
    @RequestMapping("/saleOn")
    @ResponseBody
    public AjaxResult saleOn(Long id){
        serviceItemService.saleOn(id);
        return AjaxResult.success();
    }
    // 下架
    @RequestMapping("/saleOff")
    @ResponseBody
    public AjaxResult saleOff(Long id){
        serviceItemService.saleOff(id);
        return AjaxResult.success();
    }
    // 发起审核
    @RequestMapping("/startAudit")
    @ResponseBody
    public AjaxResult startAudit(Long id,Long showOwnerId,Long financeId,String info){
        serviceItemService.startAudit(id,showOwnerId,financeId,info);
        return AjaxResult.success();
    }
}
