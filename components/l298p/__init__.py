import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import CONF_ID

# Declare the namespace for the component
l298p_ns = cg.esphome_ns.namespace('l298p')
L298P = l298p_ns.class_('L298P', cg.Component, i2c.I2CDevice)

# Define the configuration schema
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(L298P),
}).extend(i2c.I2C_DEVICE_SCHEMA(0x0f))

# Register the component
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
