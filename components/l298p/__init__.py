import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import CONF_ID, CONF_ADDRESS

# Declare the namespace for the component
l298p_ns = cg.esphome_ns.namespace("l298p")
L298P = l298p_ns.class_("L298P", cg.Component, i2c.I2CDevice)

# Define the configuration schema
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(L298P),
    cv.Optional(CONF_ADDRESS, default=0x0F): cv.i2c_address,  # Default address is 0x0F
}).extend(i2c.i2c_device_schema(0x0f))

# Register the component
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    cg.add(var.set_i2c_address(config[CONF_ADDRESS]))  # Set the I2C address
    cg.add_global(cg.RawExpression('ESP_LOGI("test", "Custom component registered.");'))
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
