/*
 * Copyright (C) 2020 Jolla Ltd.
 * Copyright (C) 2020 Open Mobile Platform LLC.
 * Copyright (C) 2020 Slava Monich <slava.monich@jolla.com>
 *
 * You may use this file under the terms of the BSD license as follows:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer
 *      in the documentation and/or other materials provided with the
 *      distribution.
 *   3. Neither the names of the copyright holders nor the names of its
 *      contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation
 * are those of the authors and should not be interpreted as representing
 * any official policies, either expressed or implied.
 */

#include "sample_plugin.h"

#include "jail_launch_hook.h"
#include "jail_plugin_impl.h"
#include "jail_plugin_module_impl.h"

typedef JailPluginClass SamplePluginClass;
typedef struct sample_plugin {
    JailPlugin parent;
    SailJail* jail;
    guint launch_hook_id;
} SamplePlugin;

G_DEFINE_TYPE(SamplePlugin, sample_plugin, JAIL_TYPE_PLUGIN)
#define TYPE (sample_plugin_get_type())
#define THIS(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE, SamplePlugin))

GLOG_MODULE_DEFINE("sample-plugin");

static
gboolean
sample_plugin_start(
    JailPlugin* plugin,
    SailJail* jail,
    GError** error)
{
    SamplePlugin* self = THIS(plugin);
    JailLaunchHook* hook = sample_launch_hook_new();

    GDEBUG("Starting sample plugin");
    self->jail = jail;
    self->launch_hook_id = jail_launch_hook_add(jail, hook);
    jail_launch_hook_unref(hook);
    return TRUE;
}

static
void
sample_plugin_stop(
    JailPlugin* plugin)
{
    SamplePlugin* self = THIS(plugin);

    GDEBUG("Stopping sample plugin");
    jail_launch_hook_remove(self->jail, self->launch_hook_id);
}

static
void
sample_plugin_init(
    SamplePlugin* self)
{
}

static
void
sample_plugin_class_init(
    SamplePluginClass* klass)
{
    klass->start = sample_plugin_start;
    klass->stop = sample_plugin_stop;
}

static
JailPlugin*
sample_plugin_create(
    const JailPluginDesc* desc,
    GError** error)
{
    return g_object_new(TYPE, NULL);
}

JAIL_PLUGIN_DEFINE(sample, "Sample SailJail plugin", sample_plugin_create)
JAIL_PLUGIN_MODULE_DEFINE("Sample SailJail plugin module")

/*
 * Local Variables:
 * mode: C
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
