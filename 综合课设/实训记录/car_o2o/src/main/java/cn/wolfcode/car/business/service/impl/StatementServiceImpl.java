package cn.wolfcode.car.business.service.impl;

import cn.wolfcode.car.business.domain.Appointment;
import cn.wolfcode.car.business.domain.Statement;
import cn.wolfcode.car.business.mapper.StatementMapper;
import cn.wolfcode.car.business.query.StatementQuery;
import cn.wolfcode.car.business.service.IAppointmentService;
import cn.wolfcode.car.business.service.IStatementService;
import cn.wolfcode.car.common.base.page.TablePageInfo;
import cn.wolfcode.car.common.exception.BusinessException;
import cn.wolfcode.car.common.util.Convert;
import cn.wolfcode.car.shiro.ShiroUtils;
import com.github.pagehelper.PageHelper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Date;
import java.util.List;

@Service
@Transactional
public class StatementServiceImpl implements IStatementService {

    @Autowired
    private StatementMapper statementMapper;
    @Autowired
    private IAppointmentService appointmentService;


    @Override
    public TablePageInfo<Statement> query(StatementQuery qo) {
        PageHelper.startPage(qo.getPageNum(), qo.getPageSize());
        return new TablePageInfo<Statement>(statementMapper.selectForList(qo));
    }


    @Override
    public void save(Statement statement) {
        // 从安全角度考虑，前台传递过来的对象是不可以直接使用的。
        // 所以我们都新建对象。这样无论如何都不会因为前台传递了默认值而改变我们的默认值数据。
        Statement obj = new Statement();
        obj.setCustomerName(statement.getCustomerName());
        obj.setCustomerPhone(statement.getCustomerPhone());
        obj.setActualArrivalTime(statement.getActualArrivalTime());
        obj.setLicensePlate(statement.getLicensePlate());
        obj.setCarSeries(statement.getCarSeries());
        obj.setServiceType(statement.getServiceType());
        obj.setCreateTime(new Date());
        obj.setInfo(statement.getInfo());
        statementMapper.insert(obj);
    }

    @Override
    public Statement get(Long id) {
        return statementMapper.selectByPrimaryKey(id);
    }


    @Override
    public void update(Statement statement) {
        Statement obj = this.get(statement.getId());
        // 只有状态为预约中才可以点击编辑按钮。其他都不可以。
        if(Statement.STATUS_PAID.equals(obj.getStatus())){
            throw new RuntimeException("已支付的结算单不允许进行修改");
        }
        obj.setCustomerName(statement.getCustomerName());
        obj.setCustomerPhone(statement.getCustomerPhone());
        obj.setActualArrivalTime(statement.getActualArrivalTime());
        obj.setLicensePlate(statement.getLicensePlate());
        obj.setCarSeries(statement.getCarSeries());
        obj.setServiceType(statement.getServiceType());
        obj.setInfo(statement.getInfo());
        statementMapper.updateByPrimaryKey(obj);
    }

    @Override
    public void deleteBatch(String ids) {
        Long[] dictIds = Convert.toLongArray(ids);
        for (Long dictId : dictIds) {
            statementMapper.deleteByPrimaryKey(dictId);
        }
    }

    @Override
    public List<Statement> list() {
        return statementMapper.selectAll();
    }

    @Override
    public void remove(Long[] ids) {
        if(ids != null && ids.length > 0){
            for (Long id : ids) {
                statementMapper.changeIsDeleteById(id,Statement.IS_DELETE);
            }
        }
    }

    @Override
    @Transactional
    public void pay(Long statementId) {
        // - 根据传入的 id 查询出当前结算单的信息。
        Statement statement = this.get(statementId);
        // - 判断其状态必须为 消费中 才可以进行支付。
        if(Statement.STATUS_PAID.equals(statement.getStatus())){
            throw new BusinessException("请不要重复支付");
        }
        // - 在结算单中记录收款人和收款时间。
        statement.setPayee(ShiroUtils.getUser());
        statement.setPayTime(new Date());
        // - 将结算单状态修改为已支付。
        statement.setStatus(Statement.STATUS_PAID);
        // - 修改结算单状态
        statementMapper.update(statement);
        // - 判定结算单中的预约单 id 是否存在
        if(statement.getAppointmentId() != null){
            // - 若存在则说明该结算单是预约单生成的。需要将预约单的状态修改为已支付。
            appointmentService.changeStatus(statement.getAppointmentId(), Appointment.STATUS_PAID);
        }
    }

    @Override
    public Long generateStatement(Long appointmentId) {
        Statement statement = statementMapper.getByAppointmentId(appointmentId);
        Appointment appointment = appointmentService.get(appointmentId);
        // 没有通过该预约单 id 查询到对应的结算单。并且 该预约单的状态是已到店
        if(statement == null && Appointment.STATUS_ARRIVAL.equals(appointment.getStatus())){
            // 生成结算单
            statement = new Statement();
            statement.setCustomerName(appointment.getCustomerName());
            statement.setCustomerPhone(appointment.getCustomerPhone());
            statement.setActualArrivalTime(appointment.getActualArrivalTime());
            statement.setLicensePlate(appointment.getLicensePlate());
            statement.setCarSeries(appointment.getCarSeries());
            statement.setServiceType(appointment.getServiceType());
            statement.setAppointmentId(appointmentId);
            statement.setCreateTime(new Date());
            statement.setInfo(statement.getInfo());
            statementMapper.insert(statement);
            // 更新预约单状态
            appointmentService.changeStatus(appointmentId,Appointment.STATUS_SETTLE);
        }
        return statement.getId();
    }
}
