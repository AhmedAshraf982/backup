import clx.xms
client = clx.xms.Client('abdef8db378442bdae9fc7a87d481ab9', '2961165a62694b78a4f5a6d7f3b6cff3')

try:
    batch_params = clx.xms.api.MtBatchTextSmsCreate()
    batch_params.sender = '+447537455184'
    batch_params.recipients = ['+923312729490']
    batch_params.body = 'Hello, ${name}!'
    batch_params.parameters = {
            'name': {
                '923312729490': 'Ahmed'
            }
        }

    batch = client.create_text_batch(batch_params)
    print('The batch was given ID %s' % batch.batch_id)
except Exception as ex:
    print('Error creating batch: %s' % str(ex))