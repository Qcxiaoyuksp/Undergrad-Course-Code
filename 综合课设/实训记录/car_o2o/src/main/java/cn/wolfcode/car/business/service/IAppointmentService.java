package cn.wolfcode.car.business.service;

import cn.wolfcode.car.business.domain.Appointment;
import cn.wolfcode.car.business.query.AppointmentQuery;
import cn.wolfcode.car.common.base.page.TablePageInfo;

import java.util.List;

/**
 * 养修预约接口
 */
public interface IAppointmentService {

    /**
     * 分页
     * @param qo
     * @return
     */
    TablePageInfo<Appointment> query(AppointmentQuery qo);


    /**
     * 查单个
     * @param id
     * @return
     */
    Appointment get(Long id);


    /**
     * 保存
     * @param Appointment
     */
    void save(Appointment appointment);

  
    /**
     * 更新
     * @param Appointment
     */
    void update(Appointment appointment);

    /**
     *  批量删除
     * @param ids
     */
    void deleteBatch(String ids);

    /**
     * 查询全部预约用户
     * @return
     */
    List<Appointment> list();

    /**
     * 到店功能
     * @param id
     */
    void arrival(Long id);

    /**
     * 取消功能
     * @param id
     */
    void cancel(Long id);

    /**
     * 批量软删除
     * @param ids
     */
    void remove(Long[] ids);

    /**
     * 修改预约单状态为已支付
     * @param appointmentId
     * @param statusPaid
     */
    void changeStatus(Long appointmentId, Integer statusPaid);
}
